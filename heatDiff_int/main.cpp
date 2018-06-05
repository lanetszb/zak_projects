#include <iostream>
#include <cmath>
#include <vector>
#include <GetFromFile.h>
#include <iomanip>
#include <iostream>

void funcJacobi(const std::vector<double> &val, const std::vector<int> &col,
                const std::vector<int> &poi, const std::vector<double> &B,
                std::vector<double> &X, const double &maxTolerance);

void funcCond(std::vector<double> &cond, const std::vector<double> &T);

void funcDens(std::vector<double> &dens, const std::vector<double> &T);

void funcLamb(std::vector<double> &lamb, const std::vector<double> &T);

void funcVal(std::vector<double> &val, const std::vector<double> &Ai, const std::vector<double> &Bi,
             const std::vector<double> &Ci, const std::vector<double> &h, const int &N);

void funcCol(std::vector<int> &col, const int &N);

void funcPoi(std::vector<int> &poi, const int &N);

void func_vecB(std::vector<double> &B, const int &N, const int &Tl,
               const int &Tr, const std::vector<double> &h, const std::vector<double> &T);

void func_eachWhich(const int &eachWhich, const int iter, const std::vector<double> &T, const double &dx);

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
    auto maxTolerance = dataFile.getWord<double>("MAX_TOLERANCE");

    // ***Numerical solution for heat diffusion begins here***
    double dx = l / (N + 1); // (m);
    double V = dx * dx;

    // Temp vector
    std::vector<double> T(N + 1, T0);
    T[0] = Tl;
    T[N] = Tr;

    int iter = 0;

    for (double t = 0; t <= time; t += dt, iter++) {
        // Temperature graphs output at different time steps
        int eachWhich = 50;
        func_eachWhich(eachWhich, iter, T, dx);

        // Conductivity vector
        std::vector<double> cond(N + 1, 0);
        funcCond(cond, T);

        // Dens vector
        std::vector<double> dens(N + 1, 0);
        funcDens(dens, T);

        // h coeff vector
        std::vector<double> h(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            h[i] = cond[i] * dens[i] * V / dt;

        // Lambda vector
        std::vector<double> lamb(N + 1, 0);
        funcLamb(lamb, T);

        // LambMinus
        std::vector<double> lambMinus(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            lambMinus[i] =
                    (2 * lamb[i] * lamb[i - 1]) / (lamb[i - 1] + lamb[i]);

        // lambPlus
        std::vector<double> lambPlus(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            lambPlus[i] =
                    (2 * lamb[i] * lamb[i + 1]) / (lamb[i + 1] + lamb[i]);

        // Ai coeff vector
        std::vector<double> Ai(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            Ai[i] = -lambMinus[i] / dx;

        // Ci coeff vector
        std::vector<double> Ci(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            Ci[i] = -lambPlus[i] / dx;

        // Bi coeff vector
        std::vector<double> Bi(N + 1, 0);
        for (int i = 0; i < T.size(); i++)
            Bi[i] = h[i] - Ci[i] - Ai[i];

        //automatically generated vector val
        std::vector<double> val((N - 1) * 3 + 2, 0);
        funcVal(val, Ai, Bi, Ci, h, N);

        //automatically generated vector col
        std::vector<int> col(val.size(), 0);
        funcCol(col, N);

        //automatically generated vector poi
        std::vector<int> poi(N + 2, 0);
        funcPoi(poi, N);

        // automatically generated vector B
        std::vector<double> B(N + 1, T0);
        func_vecB(B, N, Tl, Tr, h, T);

        // running Jacobi solver
        funcJacobi(val, col, poi, B, T, maxTolerance);
    }

    // ***the main code ends here***


    // Temperature vector ouptput to console
    for (int i = 0; i < T.size(); i++)
        std::cout << T[i] << std::endl;
    std::cout << std::endl;

    // ***data output***
    std::ofstream oStream;

    // data output temperature
    std::string Temp = "out.plt";
    oStream.open(Temp.c_str());
    oStream.precision(7);
    int w = 15;
    oStream.setf(std::ios::scientific, std::ios::floatfield);

    double L = 0;
    oStream << "set term png" << std::endl;
    oStream << "set output 'out.png'" << std::endl;
    oStream << "set ylabel 'Temperature, (celc)'" << std::endl;
    oStream << "set xlabel 'Length, (m)'" << std::endl;
    oStream << "plot '-' using 1:2 w l" << std::endl;

    for (int i = 0; i < T.size(); i++, L += dx)
        oStream << std::setw(w) << L << std::setw(w) << T[i] << std::endl;
    oStream << "end" << std::endl;
    oStream.close();

    //data output density
    std::string Dens = "dens.plt";
    oStream.open(Dens.c_str());
    oStream.precision(7);
    w = 15;
    oStream.setf(std::ios::scientific, std::ios::floatfield);

    std::vector<double> dens(N + 1, 0);
    funcDens(dens, T);

    oStream << "set term png" << std::endl;
    oStream << "set output 'dens.png'" << std::endl;
    oStream << "set xlabel 'Temperature, (celc)'" << std::endl;
    oStream << "set ylabel 'Density, (kg/m3)'" << std::endl;
    oStream << "plot '-' using 1:2 w l" << std::endl;

    for (int i = 0; i < T.size(); i++)
        oStream << std::setw(w) << T[i] << std::setw(w) << dens[i]
                << std::endl;
    oStream << "end" << std::endl;
    oStream.close();

    // data output conductivity
    std::string Cond = "cond.plt";
    oStream.open(Cond.c_str());
    oStream.precision(7);
    w = 15;
    oStream.setf(std::ios::scientific, std::ios::floatfield);

    std::vector<double> cond(N + 1, 0);
    funcCond(cond, T);

    oStream << "set term png" << std::endl;
    oStream << "set output 'cond.png'" << std::endl;
    oStream << "set xlabel 'Temperature, (celc)'" << std::endl;
    oStream << "set ylabel 'Conductivity, (J/kg K)'" << std::endl;
    oStream << "plot '-' using 1:2 w l" << std::endl;

    for (int i = 0; i < T.size(); i++)
        oStream << std::setw(w) << T[i] << std::setw(w) << cond[i]
                << std::endl;
    oStream << "end" << std::endl;
    oStream.close();

    //data output lamb
    std::string Lamb = "lamb.plt";
    oStream.open(Lamb.c_str());
    oStream.precision(7);
    w = 15;
    oStream.setf(std::ios::scientific, std::ios::floatfield);

    std::vector<double> lamb(N + 1, 0);
    funcLamb(lamb, T);

    oStream << "set term png" << std::endl;
    oStream << "set output 'lamb.png'" << std::endl;
    oStream << "set xlabel 'Temperature, (celc)'" << std::endl;
    oStream << "set ylabel 'Lambda, (W/m K)'" << std::endl;
    oStream << "plot '-' using 1:2 w l" << std::endl;
    oStream << "plot '-' using 1:2 w l" << std::endl;

    for (int i = 0; i < T.size(); i++)
        oStream << std::setw(w) << T[i] << std::setw(w) << lamb[i]
                << std::endl;
    oStream << "end" << std::endl;
    oStream.close();

    std::string plotTemp = "gnuplot " + Temp + "&& open out.png";
    std::string plotDens = "gnuplot " + Dens + "&& open dens.png";
    std::string plotCond = "gnuplot " + Cond + "&& open cond.png";
    std::string plotLamb = "gnuplot " + Lamb + "&& open lamb.png";

    std::cout << system(plotTemp.c_str()) << std::endl;
    std::cout << system(plotDens.c_str()) << std::endl;
    std::cout << system(plotCond.c_str()) << std::endl;
    std::cout << system(plotLamb.c_str()) << std::endl;

    return 0;
}

// ***all the functions are described below***

void func_eachWhich(const int &eachWhich, const int iter, const std::vector<double> &T, const double &dx) {


    if (iter % eachWhich == 0) {
        std::string tStep =
                "tStep_no_" + std::to_string(iter) + ".plt";

        std::ofstream oStream;
        oStream.open(tStep.c_str());

        oStream.precision(7); // Количество знаков после запятой.
        int w = 15; // Переменная для общего количества знаков.
        // oStream.setf(std::ios::fixed, std::ios::floatfield);
        oStream.setf(std::ios::scientific, std::ios::floatfield);

        oStream << "set term png" << std::endl;
        oStream << "set output 'tStep_no" + std::to_string(iter) + ".png'" << std::endl;
        oStream << "set ylabel 'Temperature, (celc)'" << std::endl;
        oStream << "set xlabel 'Length, (m)'" << std::endl;

        double L = 0;
        oStream << "plot '-' using 1:2 w l" << std::endl;
        for (int i = 0; i < T.size(); i++, L += dx)
            oStream << std::setw(w) << L << std::setw(w) << T[i]
                    << std::endl;
        oStream << "end" << std::endl;
        oStream.close();

        std::string plot_tStep = "gnuplot " + tStep + "&& open 'tStep_no" + std::to_string(iter) + ".png'";
        std::cout << system(plot_tStep.c_str()) << std::endl;
    }
}

void func_vecB(std::vector<double> &B, const int &N, const int &Tl,
               const int &Tr, const std::vector<double> &h, const std::vector<double> &T) {

    for (int i = 0; i < T.size(); i++)
        B[i] = T[i] * h[i];
    B[0] = Tl * h[0];
    B[N] = Tr * h[N];
}

void funcPoi(std::vector<int> &poi, const int &N) {

    for (int i = 1, j = 1; i <= N; i++, j += 3)
        poi[i] = j;

    poi[0] = 0;
    poi[N + 1] = poi[N] + 1;
}

void funcCol(std::vector<int> &col, const int &N) {

    for (int i = 1, j = 0; i < col.size(); i += 3, j++)
        col[i] = j;

    for (int i = 2, j = 1; i < col.size(); i += 3, j++)
        col[i] = j;

    for (int i = 3, j = 2; i < col.size(); i += 3, j++)
        col[i] = j;

    col[0] = 0;
    col[(N - 1) * 3 + 1] = N;
}

void funcVal(std::vector<double> &val, const std::vector<double> &Ai, const std::vector<double> &Bi,
             const std::vector<double> &Ci, const std::vector<double> &h, const int &N) {

    for (int i = 1, j = 1; i < val.size(); i += 3, j++)
        val[i] = Ai[j];

    for (int i = 2, j = 1; i < val.size(); i += 3, j++)
        val[i] = Bi[j];

    for (int i = 3, j = 1; i < val.size(); i += 3, j++)
        val[i] = Ci[j];

    val[0] = h[0];
    val[(N - 1) * 3 + 1] = h[N];
}

void funcLamb(std::vector<double> &lamb, const std::vector<double> &T) {

    for (int i = 0; i < T.size(); i++) {

        if (T[i] >= 0 && T[i] < 800)
            lamb[i] = 54 - 3.33 * 1.0E-2 * T[i];

        else if (T[i] >= 800 && T[i] < 1200)
            lamb[i] = 27.3;
    }
}

void funcDens(std::vector<double> &dens, const std::vector<double> &T) {

    for (int i = 0; i < T.size(); i++) {

        if (T[i] >= 0 && T[i] < 700)
            dens[i] = -0.32142857 * T[i] + 7850;

        else if (T[i] >= 700 && T[i] < 820)
            dens[i] = 7625;

        else if (T[i] >= 820 && T[i] < 1200)
            dens[i] = -0.59643 * T[i] + 8114.0714;
    }
}

void funcCond(std::vector<double> &cond, const std::vector<double> &T) {

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