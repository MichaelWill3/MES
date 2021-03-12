#include "H.hpp"
#include "jacobi.hpp"
#include "integrationPoint.hpp"
#include "IntegrationPoints.hpp"
#include "settings.hpp"
#include <iostream>
void H2(Element* e, std::vector<std::vector<double>> &H_, std::vector<std::vector<double>> &C_, std::vector<double> &P_)
{
    auto J = jacobi2p(e);

    std::vector<std::vector<std::vector<double>>> inverseJ(4, std::vector<std::vector<double>>(2, std::vector<double>(2)));

    int ips = 4;

    std::vector<double> detJ(4);
    for (int ip = 0; ip < ips; ip++)
    {
        detJ[ip] = J[ip][0][0] * J[ip][1][1] - J[ip][1][0] * J[ip][0][1];

        inverseJ[ip][0][0] = J[ip][1][1] / detJ[ip];
        inverseJ[ip][0][1] = -J[ip][0][1] / detJ[ip];
        inverseJ[ip][1][0] = -J[ip][1][0] / detJ[ip];
        inverseJ[ip][1][1] = J[ip][0][0] / detJ[ip];
    }

    std::vector<std::vector<double>> dNdx(4, std::vector<double>(4));
    std::vector<std::vector<double>> dNdy(4, std::vector<double>(4));

    IntegrationPoints<2> IPs2;

    double (*N[4])(IntegrationPoint);
    N[0] = [](IntegrationPoint p) {return 0.25 * (1 - p.location.x) * (1 - p.location.y); };
    N[1] = [](IntegrationPoint p) {return 0.25 * (1 + p.location.x) * (1 - p.location.y); };
    N[2] = [](IntegrationPoint p) {return 0.25 * (1 + p.location.x) * (1 + p.location.y); };
    N[3] = [](IntegrationPoint p) {return 0.25 * (1 - p.location.x) * (1 + p.location.y); };

    double (*dNdksi2[4])(IntegrationPoint);
    dNdksi2[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.y) / 4; };
    dNdksi2[1] = [](IntegrationPoint p) {return  1 * (1 - p.location.y) / 4; };
    dNdksi2[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.y) / 4; };
    dNdksi2[3] = [](IntegrationPoint p) {return -1 * (1 + p.location.y) / 4; };

    double (*dNdeta2[4])(IntegrationPoint);
    dNdeta2[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.x) / 4; };
    dNdeta2[1] = [](IntegrationPoint p) {return -1 * (1 + p.location.x) / 4; };
    dNdeta2[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.x) / 4; };
    dNdeta2[3] = [](IntegrationPoint p) {return  1 * (1 - p.location.x) / 4; };

    for (int ip = 0; ip < ips; ip++)
    {

        for (int N = 0; N < 4; N++)
        {
            dNdx[ip][N] = inverseJ[ip][0][0] * dNdksi2[N](IPs2[ip]) + inverseJ[ip][0][1] * dNdeta2[N](IPs2[ip]);
            dNdy[ip][N] = inverseJ[ip][1][0] * dNdksi2[N](IPs2[ip]) + inverseJ[ip][1][1] * dNdeta2[N](IPs2[ip]);
        }
    }

    std::vector<std::vector<std::vector<double>>> dNdx2(4, std::vector< std::vector<double>>(4, std::vector<double>(4)));;
    std::vector<std::vector<std::vector<double>>> dNdy2(4, std::vector< std::vector<double>>(4, std::vector<double>(4)));;
    for (int ip = 0; ip < 4; ip++)
    {
        for (int column = 0; column < 4; column++)
        {
            for (int row = 0; row < 4; row++)
            {
                dNdx2[ip][column][row] = dNdx[ip][column] * dNdx[ip][row] * detJ[ip];
                dNdy2[ip][column][row] = dNdy[ip][column] * dNdy[ip][row] * detJ[ip];
            }
        }
    }
    // **************************************************************************************
    // **************************************************************************************
    // **************************************************************************************

    std::vector<std::vector<double>>* Hbc = new std::vector<std::vector<double>>(4, std::vector<double>(4));
    Point SurfacePoints[8];
    SurfacePoints[0] = Point(-1.0 / sqrt(3.0), -1, 0, e->points[0].boundary && e->points[1].boundary, 0);
    SurfacePoints[1] = Point(1.0 / sqrt(3.0), -1, 1, e->points[0].boundary && e->points[1].boundary, 0);
    SurfacePoints[2] = Point(1, -1.0 / sqrt(3.0), 2, e->points[1].boundary && e->points[2].boundary, 0);
    SurfacePoints[3] = Point(1, 1.0 / sqrt(3.0), 3, e->points[1].boundary && e->points[2].boundary, 0);
    SurfacePoints[4] = Point(1.0 / sqrt(3.0), 1, 4, e->points[2].boundary && e->points[3].boundary, 0);
    SurfacePoints[5] = Point(-1.0 / sqrt(3.0), 1, 5, e->points[2].boundary && e->points[3].boundary, 0);
    SurfacePoints[6] = Point(-1, 1.0 / sqrt(3.0), 6, e->points[3].boundary && e->points[0].boundary, 0);
    SurfacePoints[7] = Point(-1, -1.0 / sqrt(3.0), 7, e->points[3].boundary && e->points[0].boundary, 0);

    double wbc[8][2];
    for (int i = 0; i < 8; i++)
    {
        wbc[i][0] = SurfacePoints[i].boundary ? 1.0 : 0.0;
        wbc[i][1] = SurfacePoints[i].boundary ? 1.0 : 0.0;
    }

    IntegrationPoint* ipsbc[8];
    for (int i = 0; i < 8; i++)
        ipsbc[i] = new IntegrationPoint(SurfacePoints[i], wbc[i]);

    std::vector<double> *P = new std::vector<double>(4);

    for (int surface = 0; surface < 4; surface++)
    {
        Point P1 = e->points[surface];
        Point P2 = e->points[(surface + 1) % 4];

        if (!(P1.boundary && P2.boundary)) continue;

        double detJBC = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2)) / 2;
        for (int ip = 2 * surface; ip < (2 * surface + 2); ip++)
        {
            for (int column = 0; column < 4; column++)
            {
                (*P)[column] += settings.convection * settings.ambient_temperature * detJBC * N[column](*ipsbc[ip]);
                for (int row = 0; row < 4; row++)
                {
                    (*Hbc)[column][row] += detJBC
                        * settings.convection
                        * N[column](*ipsbc[ip])
                        * N[row](*ipsbc[ip]);
                }
            }
        }
    }
    // **************************************************************************************
    // **************************************************************************************
    // **************************************************************************************
    std::vector<std::vector<double>> *H = new std::vector<std::vector<double>>(4, std::vector<double>(4));
    std::vector<std::vector<double>> *C = new std::vector<std::vector<double>>(4, std::vector<double>(4));
    for (int ip = 0; ip < ips; ip++)
    {
        for (int column = 0; column < 4; column++)
        {
            for (int row = 0; row < 4; row++)
            {
                (*H)[column][row] += settings.conductivity * (dNdx2[ip][column][row] + dNdy2[ip][column][row]) * IPs2[ip].weight[0] * IPs2[ip].weight[1];
                (*C)[column][row] += settings.density * settings.specific_heat * detJ[ip] * N[row](IPs2[ip]) * N[column](IPs2[ip]) * IPs2[ip].weight[0] * IPs2[ip].weight[1];
            }
        }
    }

    for (int column = 0; column < 4; column++)
        for (int row = 0; row < 4; row++)
            (*H)[column][row] += (*Hbc)[column][row];

    H_ = *H;
    C_ = *C;
    P_ = *P;

    //return H_;
}

void H3(Element* e, std::vector<std::vector<double>> &H_, std::vector<std::vector<double>> &C_, std::vector<double>& P_)
{
    auto J = jacobi3p(e);

    std::vector<std::vector<std::vector<double>>> inverseJ(9, std::vector<std::vector<double>>(2, std::vector<double>(2)));

    int ips = 9;

    std::vector<double> detJ(9);
    for (int ip = 0; ip < 9; ip++)
    {
        detJ[ip] = J[ip][0][0] * J[ip][1][1] - J[ip][1][0] * J[ip][0][1];

        inverseJ[ip][0][0] = J[ip][1][1] / detJ[ip];
        inverseJ[ip][0][1] = -J[ip][0][1] / detJ[ip];
        inverseJ[ip][1][0] = -J[ip][1][0] / detJ[ip];
        inverseJ[ip][1][1] = J[ip][0][0] / detJ[ip];
    }

    std::vector<std::vector<double>> dNdx(9, std::vector<double>(4));
    std::vector<std::vector<double>> dNdy(9, std::vector<double>(4));

    IntegrationPoints<3> IPs3;

    double (*N[4])(IntegrationPoint);
    N[0] = [](IntegrationPoint p) {return 0.25 * (1 - p.location.x) * (1 - p.location.y); };
    N[1] = [](IntegrationPoint p) {return 0.25 * (1 + p.location.x) * (1 - p.location.y); };
    N[2] = [](IntegrationPoint p) {return 0.25 * (1 + p.location.x) * (1 + p.location.y); };
    N[3] = [](IntegrationPoint p) {return 0.25 * (1 - p.location.x) * (1 + p.location.y); };

    double (*dNdksi2[4])(IntegrationPoint);
    dNdksi2[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.y) / 4; };
    dNdksi2[1] = [](IntegrationPoint p) {return  1 * (1 - p.location.y) / 4; };
    dNdksi2[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.y) / 4; };
    dNdksi2[3] = [](IntegrationPoint p) {return -1 * (1 + p.location.y) / 4; };

    double (*dNdeta2[4])(IntegrationPoint);
    dNdeta2[0] = [](IntegrationPoint p) {return -1 * (1 - p.location.x) / 4; };  
    dNdeta2[1] = [](IntegrationPoint p) {return -1 * (1 + p.location.x) / 4; };
    dNdeta2[2] = [](IntegrationPoint p) {return  1 * (1 + p.location.x) / 4; };
    dNdeta2[3] = [](IntegrationPoint p) {return  1 * (1 - p.location.x) / 4; };

    for (int ip = 0; ip < ips; ip++)
    {

        for (int N = 0; N < 4; N++)
        {
            dNdx[ip][N] = inverseJ[ip][0][0] * dNdksi2[N](IPs3[ip]) + inverseJ[ip][0][1] * dNdeta2[N](IPs3[ip]);
            dNdy[ip][N] = inverseJ[ip][1][0] * dNdksi2[N](IPs3[ip]) + inverseJ[ip][1][1] * dNdeta2[N](IPs3[ip]);
        }
    }

    std::vector<std::vector<std::vector<double>>> dNdx2(9, std::vector< std::vector<double>>(4, std::vector<double>(4)));;
    std::vector<std::vector<std::vector<double>>> dNdy2(9, std::vector< std::vector<double>>(4, std::vector<double>(4)));;
    for (int ip = 0; ip < ips; ip++)
    {
        for (int column = 0; column < 4; column++)
        {
            for (int row = 0; row < 4; row++)
            {
                dNdx2[ip][column][row] = dNdx[ip][column] * dNdx[ip][row] * detJ[ip];
                dNdy2[ip][column][row] = dNdy[ip][column] * dNdy[ip][row] * detJ[ip];
            }
        }
    }
    //*************************************************************************************************
    //*************************************************************************************************
    //*************************************************************************************************

    std::vector<std::vector<double>>* Hbc = new std::vector<std::vector<double>>(4, std::vector<double>(4));
    Point SurfacePoints[12];

    double coords[3] = {
        -sqrt(3.0 / 5.0),
        0,
        sqrt(3.0 / 5.0)
    };
    double weights[3] = {
        5.0 / 9.0,
        8.0 / 9.0,
        5.0 / 9.0
    };

    SurfacePoints[0] = Point(-sqrt(3.0 / 5.0), -1, 0, e->points[0].boundary && e->points[1].boundary, 0);
    SurfacePoints[1] = Point(0, -1, 1, e->points[0].boundary && e->points[1].boundary, 0);
    SurfacePoints[2] = Point(sqrt(3.0 / 5.0), -1, 2, e->points[0].boundary && e->points[1].boundary, 0);
    SurfacePoints[3] = Point(1, -sqrt(3.0 / 5.0), 3, e->points[1].boundary && e->points[2].boundary, 0);
    SurfacePoints[4] = Point(1, 0, 4, e->points[1].boundary && e->points[2].boundary, 0);
    SurfacePoints[5] = Point(1, sqrt(3.0 / 5.0), 5, e->points[1].boundary && e->points[2].boundary, 0);
    SurfacePoints[6] = Point(sqrt(3.0 / 5.0), 1, 6, e->points[2].boundary && e->points[3].boundary, 0);
    SurfacePoints[7] = Point(0, 1, 7, e->points[2].boundary && e->points[3].boundary, 0);
    SurfacePoints[8] = Point(-sqrt(3.0 / 5.0), 1, 8, e->points[2].boundary && e->points[3].boundary, 0);
    SurfacePoints[9] = Point(-1, sqrt(3.0 / 5.0), 9, e->points[3].boundary && e->points[0].boundary, 0);
    SurfacePoints[10] = Point(-1, 0, 10, e->points[3].boundary && e->points[0].boundary, 0);
    SurfacePoints[11] = Point(-1, -sqrt(3.0 / 5.0), 11, e->points[3].boundary && e->points[0].boundary, 0);

    double wbc[12][2];

    for (int i = 0; i < 12; i++)
    {
        if (SurfacePoints[i].x == -sqrt(3.0 / 5.0) || SurfacePoints[i].x == sqrt(3.0 / 5.0))
            wbc[i][0] = 5.0 / 9.0;
        else if (SurfacePoints[i].x == 0)
            wbc[i][0] = 8.0 / 9.0;
        else wbc[i][0] = 1;


        if (SurfacePoints[i].y == -sqrt(3.0 / 5.0) || SurfacePoints[i].y == sqrt(3.0 / 5.0))
            wbc[i][1] = 5.0 / 9.0;
        else if (SurfacePoints[i].y == 0)
            wbc[i][1] = 8.0 / 9.0;
        else wbc[i][1] = 1;
    }
    IntegrationPoint* ipsbc[12];
    for (int i = 0; i < 12; i++)
        ipsbc[i] = new IntegrationPoint(SurfacePoints[i], wbc[i]);

    std::vector<double>* P = new std::vector<double>(4);

    for (int surface = 0; surface < 4; surface++)
    {
        Point P1 = e->points[surface];
        Point P2 = e->points[(surface + 1) % 4];

        if (!(P1.boundary && P2.boundary)) continue;

        double detJBC = sqrt(pow(P1.x - P2.x, 2) + pow(P1.y - P2.y, 2)) / 2;
        for (int ip = 3 * surface; ip < (3 * surface + 3); ip++)
            for (int column = 0; column < 4; column++)
            {
                (*P)[column] += settings.convection * settings.ambient_temperature * detJBC * N[column](*ipsbc[ip]) * ipsbc[ip]->weight[0] * ipsbc[ip]->weight[1];

                for (int row = 0; row < 4; row++)
                {
                    (*Hbc)[column][row] += detJBC
                        * settings.convection
                        * N[column](*ipsbc[ip])
                        * N[row](*ipsbc[ip])
                        * ipsbc[ip]->weight[0]
                        * ipsbc[ip]->weight[1];
                }
            }
    }
    //*************************************************************************************************
    //*************************************************************************************************
    //*************************************************************************************************
    std::vector<std::vector<double>>* H = new std::vector<std::vector<double>>(4, std::vector<double>(4));
    std::vector<std::vector<double>>* C = new std::vector<std::vector<double>>(4, std::vector<double>(4));
    for (int ip = 0; ip < ips; ip++)
    {
        for (int column = 0; column < 4; column++)
        {
            for (int row = 0; row < 4; row++)
            {
                (*H)[column][row] += settings.conductivity * (dNdx2[ip][column][row] + dNdy2[ip][column][row]) * IPs3[ip].weight[0] * IPs3[ip].weight[1];
                (*C)[column][row] += settings.density * settings.specific_heat * detJ[ip] * N[row](IPs3[ip]) * N[column](IPs3[ip]) * IPs3[ip].weight[0] * IPs3[ip].weight[1];
            }
        }
    }

    for (int column = 0; column < 4; column++)
        for (int row = 0; row < 4; row++)
            (*H)[column][row] += (*Hbc)[column][row];

    C_ = *C;
    H_ = *H;
    P_ = *P;
}

void integrated_H(std::vector<Element*> elements, std::vector<std::vector<double>> &H_, std::vector<std::vector<double>> &C_, std::vector<double> &P_)
{
    std::vector<std::vector<double>>* H = new std::vector<std::vector<double>>(
        settings.grid_n_of_elems_horizontally * settings.grid_n_of_elems_vertically,
        std::vector<double>(settings.grid_n_of_elems_horizontally * settings.grid_n_of_elems_vertically));

    std::vector<std::vector<double>>* C = new std::vector<std::vector<double>>(
        settings.grid_n_of_elems_horizontally * settings.grid_n_of_elems_vertically,
        std::vector<double>(settings.grid_n_of_elems_horizontally * settings.grid_n_of_elems_vertically));

    std::vector<double>* P = new std::vector<double>(settings.grid_n_of_elems_horizontally * settings.grid_n_of_elems_vertically);

    for (Element* e : elements)
    {
        std::vector<std::vector<double>> H_local(4, std::vector<double>(4));
        std::vector<std::vector<double>> C_local(4, std::vector<double>(4));
        std::vector<double> P_local(4);
        if(settings.integration_method == 3)
            H3(e, H_local, C_local, P_local);
        else
            H2(e, H_local, C_local, P_local);
        for (int r = 0; r < 4; r++)
        {
            (*P)[e->points[r].index] += P_local[r];
            for (int c = 0; c < 4; c++)
            {
                (*H)[e->points[c].index][e->points[r].index] += H_local[c][r];
                (*C)[e->points[c].index][e->points[r].index] += C_local[c][r];
            }
        }
    }
    H_ = *H;
    C_ = *C;
    P_ = *P;
}
