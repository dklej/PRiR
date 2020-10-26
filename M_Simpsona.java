package dk;

public class M_Simpsona extends Thread {
    double f(double x) {
        return (Math.pow(x,4) - 3*x) / Math.sqrt(x*x + x); //wybrana funcja
    }

    double startFigury, koniecFigury, n;
    int iloscP = (int) n;
    double suma = 0;

    //konstruktor
    public M_Simpsona(double a, double b){
        this.startFigury = a;
        this.koniecFigury = b;
        this.n = 50;
    }

    public void run() {
        double[] punktyOX = new double[iloscP + 1];
        for (int i = 0; i <= n; i++) {
            double x = startFigury + i / n * (koniecFigury - startFigury);
            punktyOX[i] = x;
        }

        double[] punktyT = new double[iloscP];
        for (int i = 0; i < n; i++) {
            double x = (punktyOX[i + 1] + punktyOX[i]) / 2;
            punktyT[i] = x;
        }

        double h = (punktyOX[2] - punktyOX[1]) / 2;


        for (int i = 0; i < punktyOX.length - 1; i++) {
            suma += (f(punktyOX[i]) + 4 * f(punktyT[i]) + f(punktyOX[i + 1])) * h / 3;
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(suma);
        }
    }


}


