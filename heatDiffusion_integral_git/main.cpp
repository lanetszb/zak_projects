#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>

void funcJacobi(const std::vector<double> &val, const std::vector<int> &col,
                const std::vector<int> &poi, const std::vector<double> &B,
                std::vector<double> &X, const double &maxTolerance);

int main(int narg, char **arg) {
    // reading data file

    GetFromFile dataFile(arg[1]);

    auto dt = dataFile.getWord<double>("timeStep");
    auto time = dataFile.getWord<double>("time");
    auto Tl = dataFile.getWord<double>("tempLeft");
    auto Tr = dataFile.getWord<double>("tempRight");
    auto T0 = dataFile.getWord<double>("tempIni");
    auto l = dataFile.getWord<double>("length");
    auto N = dataFile.getWord<double>("gridsNumber");

    std::cout << "timeInterval " << dt << std::endl << std::endl << std::endl;

    // Numerical solution for heat diffusion begins

    double dx = l / (N + 1); // (m);
    double V = dx * dx;

    // Temp vector

    std::vector<double> T(N + 1, T0);
    T[0] = Tl;
    T[N] = Tr;

    std::ofstream oStream;
    int eachWhich = 50;
    int tN = 0;

    for (double t = 0; t <= time; t += dt, tN++) {

        if (tN % eachWhich == 0) {
            {
                std::string fileName5 =
                        "file_no_" + std::to_string(tN) + ".plt";

                oStream.open(fileName5.c_str());

                oStream.precision(7); // Количество знаков после запятой.
                int w = 15; // Переменная для общего количества знаков.
                // oStream.setf(std::ios::fixed, std::ios::floatfield);
                oStream.setf(std::ios::scientific, std::ios::floatfield);

                double L = 0;
                oStream << "plot '-' using 1:2 w l" << std::endl;
                for (int i = 0; i < T.size(); i++, L += dx)
                    oStream << std::setw(w) << L << std::setw(w) << T[i]
                            << std::endl;
                oStream << "end" << std::endl;
                oStream << "pause -1" << std::endl;
                oStream.close();
            }
        }

        // Cond vector

        std::vector<double> cond(N + 1, 0);

        for (int i = 0; i < T.size(); i++) {

            if (T[i] >= 0 && T[i] < 600)
                cond[i] =
                        425 + 7.73 * 1E-1 * T[i] - 1.69 * 1E-3 * T[i] * T[i] +
                        2.22 * 1E-6 * T[i] * T[i] * T[i];

            else if (T[i] >= 600 && T[i] < 735)
                cond[i] = 666 + 13002 / (738 - T[i]);

            else if (T[i] >= 735 && T[i] < 900)
                cond[i] = 545 + 17802 / (T[i] - 731);

            else if (T[i] >= 900 && T[i] < 1200)
                cond[i] = 650;
        }

        // Dens vector

        std::vector<double> dens(N + 1, 0);
        for (int i = 0; i < T.size(); i++) {

            if (T[i] >= 0 && T[i] < 700)
                dens[i] = -0.32142857 * T[i] + 7850;

            else if (T[i] >= 700 && T[i] < 820)
                dens[i] = 7625;

            else if (T[i] >= 820 && T[i] < 1200)
                dens[i] = -0.59643 * T[i] + 8114.0714;
        }

        // h coeff vector

        std::vector<double> h(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            h[i] = cond[i] * dens[i] * V / dt;

        // Lambda vector

        std::vector<double> lamb(N + 1, 0);
        for (int i = 0; i < T.size(); i++) {

            if (T[i] >= 0 && T[i] < 800)
                lamb[i] = 54 - 3.33 * 1.0E-2 * T[i];

            else if (T[i] >= 800 && T[i] < 1200)
                lamb[i] = 27.3;
        }

        // lambPlus & LambMinus

        std::vector<double> lambMinus(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            lambMinus[i] =
                    (2 * lamb[i] * lamb[i - 1]) / (lamb[i - 1] + lamb[i]);

        std::vector<double> lambPlus(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            lambPlus[i] =
                    (2 * lamb[i] * lamb[i + 1]) / (lamb[i + 1] + lamb[i]);

        // Ai coeff vector

        std::vector<double> Ai(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            Ai[i] = -lambMinus[i] / dx;

        // Ci coeff vector + check

        std::vector<double> Ci(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            Ci[i] = -lambPlus[i] / dx;

        // Bi coeff vector

        std::vector<double> Bi(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            Bi[i] = h[i] - Ci[i] - Ai[i];

        //automatically generated vector val

        std::vector<double> val((N - 1) * 3 + 2, 0);

        int j = 1;
        for (int i = 1; i < val.size(); i += 3, j++)
            val[i] = Ai[j];

        j = 1;
        for (int i = 2; i < val.size(); i += 3, j++)
            val[i] = Bi[j];
        j = 1;
        for (int i = 3; i < val.size(); i += 3, j++)
            val[i] = Ci[j];

        val[0] = h[0];
        val[(N - 1) * 3 + 1] = h[N];

        //automatically generated vector col

        std::vector<int> col(val.size(), 0);

        j = 0;
        for (int i = 1; i < col.size(); i += 3, j++)
            col[i] = j;

        j = 1;
        for (int i = 2; i < col.size(); i += 3, j++)
            col[i] = j;

        j = 2;
        for (int i = 3; i < col.size(); i += 3, j++)
            col[i] = j;

        col[0] = 0;
        col[(N - 1) * 3 + 1] = N;

        //automatically generated vector poi

        std::vector<int> poi(N + 2, 0);

        j = 1;
        for (int i = 1; i <= N; i++, j += 3)
            poi[i] = j;

        poi[0] = 0;
        poi[N + 1] = poi[N] + 1;

        //automatically generated vector B

        std::vector<double> B(N + 1, T0);
        for (int i = 0; i < T.size(); i++)
            B[i] = T[i] * h[i];
        B[0] = Tl * h[0];
        B[N] = Tr * h[N];

        std::cout << "B" << std::endl;
        for (int i = 0; i < T.size(); i++)
            std::cout << B[i] << std::endl;
        std::cout << std::endl;

        funcJacobi(val, col, poi, B, T, 1.E-7);

        for (int i = 0; i < T.size(); i++)
            std::cout << T[i] << std::endl;
        std::cout << std::endl;
    }


    for (int i = 0; i < T.size(); i++)
        std::cout << T[i] << std::endl;
    std::cout << std::endl;


    //data output temp

    std::string fileName1 = "out.plt";
    std::string fileName2 = "dens.plt";
    std::string fileName3 = "cond.plt";
    std::string fileName4 = "lamb.plt";
    {

        oStream.open(fileName1.c_str());

        oStream.precision(7); // Количество знаков после запятой.
        int w = 15; // Переменная для общего количества знаков.
        // oStream.setf(std::ios::fixed, std::ios::floatfield);
        oStream.setf(std::ios::scientific, std::ios::floatfield);

        double L = 0;
        oStream << "set term png" << std::endl;
        oStream << "set output 'out.png'" << std::endl;
        oStream << "plot '-' using 1:2 w l" << std::endl;
        for (int i = 0; i < T.size(); i++, L += dx)
            oStream << std::setw(w) << L << std::setw(w) << T[i] << std::endl;
        oStream << "end" << std::endl;
        // oStream << "pause -1" << std::endl;
        oStream.close();
    }

    {
        //data output dens

        oStream.open(fileName2.c_str());

        oStream.precision(7); // Количество знаков после запятой.
        int w = 15; // Переменная для общего количества знаков.
        // oStream.setf(std::ios::fixed, std::ios::floatfield);
        oStream.setf(std::ios::scientific, std::ios::floatfield);


        std::vector<double> dens(N + 1, 0);
        for (int i = 0; i < T.size(); i++) {

            if (T[i] >= 0 && T[i] < 700)
                dens[i] = -0.32142857 * T[i] + 7850;

            else if (T[i] >= 700 && T[i] < 820)
                dens[i] = 7625;

            else if (T[i] >= 820 && T[i] < 1200)
                dens[i] = -0.59643 * T[i] + 8114.0714;
        }
        oStream << "plot '-' using 1:2 w l" << std::endl;

        for (int i = 0; i < T.size(); i++)
            oStream << std::setw(w) << T[i] << std::setw(w) << dens[i]
                    << std::endl;
        oStream << "end" << std::endl;
        oStream << "pause -1" << std::endl;
        oStream.close();
    }

    {
        //data output cond

        oStream.open(fileName3.c_str());

        oStream.precision(7); // Количество знаков после запятой.
        int w = 15; // Переменная для общего количества знаков.
        // oStream.setf(std::ios::fixed, std::ios::floatfield);
        oStream.setf(std::ios::scientific, std::ios::floatfield);


        std::vector<double> cond(N + 1, 0);

        for (int i = 0; i < T.size(); i++) {

            if (T[i] >= 0 && T[i] < 600)
                cond[i] =
                        425 + 7.73 * 1E-1 * T[i] - 1.69 * 1E-3 * T[i] * T[i] +
                        2.22 * 1E-6 * T[i] * T[i] * T[i];

            else if (T[i] >= 600 && T[i] < 735)
                cond[i] = 666 + 13002 / (738 - T[i]);

            else if (T[i] >= 735 && T[i] < 900)
                cond[i] = 545 + 17802 / (T[i] - 731);

            else if (T[i] >= 900 && T[i] < 1200)
                cond[i] = 650;
        }
        oStream << "plot '-' using 1:2 w l" << std::endl;

        for (int i = 0; i < T.size(); i++)
            oStream << std::setw(w) << T[i] << std::setw(w) << cond[i]
                    << std::endl;
        oStream << "end" << std::endl;
        oStream << "pause -1" << std::endl;
        oStream.close();
    }

    {
        //data output lamb

        oStream.open(fileName4.c_str());

        oStream.precision(7); // Количество знаков после запятой.
        int w = 15; // Переменная для общего количества знаков.
        // oStream.setf(std::ios::fixed, std::ios::floatfield);
        oStream.setf(std::ios::scientific, std::ios::floatfield);


        std::vector<double> lamb(N + 1, 0);
        for (int i = 0; i < T.size(); i++) {

            if (T[i] >= 0 && T[i] < 800)
                lamb[i] = 54 - 3.33 * 1.0E-2 * T[i];

            else if (T[i] >= 800 && T[i] < 1200)
                lamb[i] = 27.3;
        }
        oStream << "plot '-' using 1:2 w l" << std::endl;

        for (int i = 0; i < T.size(); i++)
            oStream << std::setw(w) << T[i] << std::setw(w) << lamb[i]
                    << std::endl;
        oStream << "end" << std::endl;
        oStream << "pause -1" << std::endl;
        oStream.close();
    }

    std::string command1 = "gnuplot " + fileName1 + "&& open out.png";
    std::string command2 = "gnuplot " + fileName2;
    std::string command3 = "gnuplot " + fileName3;
    std::string command4 = "gnuplot " + fileName4;

    // std::cout << system(command1.c_str()) << std::endl;
    // std::cout << system(command2.c_str()) << std::endl;
    // std::cout << system(command3.c_str()) << std::endl;
    std::cout << system(command4.c_str()) << std::endl;


    return 0;
}


void funcJacobi(const std::vector<double> &val, const std::vector<int> &col,
                const std::vector<int> &poi, const std::vector<double> &B,
                std::vector<double> &X, const double &maxTolerance) {

    double curTolerance = 0;

    std::vector<std::vector<double>> Xcur{2, X};

    std::vector<int> dgInd;
    for (int i = 0; i < poi.size() - 1; i++)
        for (int j = poi[i]; j < poi[i + 1]; j++)
            if (i == col[j]) {
                dgInd.push_back(j);
                break;
            }

    unsigned int k = 0;

    do {

        for (int i = 0; i < poi.size() - 1; i++)
            Xcur[(k + 1) % 2][i] = B[i] + Xcur[k % 2][i] * val[dgInd[i]];

        for (int i = 0; i < poi.size() - 1; i++)
            for (int j = poi[i]; j < poi[i + 1]; j++)
                Xcur[(k + 1) % 2][i] -= val[j] * Xcur[k % 2][col[j]];

        for (int i = 0; i < poi.size() - 1; i++)
            Xcur[(k + 1) % 2][i] /= val[dgInd[i]];

        curTolerance = 0;
        for (int i = 0; i < poi.size() - 1; i++)
            curTolerance += fabs(2. * (Xcur[(k + 1) % 2][i] - Xcur[k % 2][i]) /
                                 (Xcur[(k + 1) % 2][i] + Xcur[k % 2][i])) /
                            B.size();

        k++;

    } while (curTolerance > maxTolerance);

    X = Xcur[k % 2];

}