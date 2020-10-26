package dk;

public class M_trapezow extends Thread{
    double f(double x) {
        return (Math.pow(x,4) - 3*x) / Math.sqrt(x*x + x); //wybrana funcja
    }

    double startFigury;
    double koniecFigury;
    int n;
    double wynik;

    //konstruktor
    public M_trapezow(double a, double b){
        this.startFigury = a;
        this.koniecFigury = b;
        this.n = 50;
    }

    public void run(){

        double x;
        for(int i = 1; i < n; i++) {
            x = startFigury + (i/n) * (koniecFigury - startFigury);
            wynik += f(x);
        }
        wynik += f(startFigury)/2 + f(koniecFigury)/2;
        wynik = wynik * (koniecFigury - startFigury)/n;
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println(wynik);
    }
}
