package dk;

public class M_prostokatow extends Thread {

    double f(double x) {
        return (Math.pow(x,4) - 3*x) / Math.sqrt(x*x + x); //wybrana funcja
    }

    double startFigury;
    double koniecFigury;
    int n;
    double wynik;

    //konstruktor
    public M_prostokatow(double a, double b){
        this.startFigury = a;
        this.koniecFigury = b;
        this.n = 50;
    }

    public void run(){
        wynik = 0;
        double wysokoscH = (koniecFigury - startFigury) / n;
        for(int i = 1; i <= n; i++) {
            wynik += f(startFigury + i * wysokoscH);
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println(wynik);
        }
        wynik *= wysokoscH;
    }
}
