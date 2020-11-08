package dk;

public class Main {
    static int ilosc_pociagow = 20;
    static int ilosc_torow = 2;
    static Stacja Stacja;


    public static void main(String[] args) {
        Stacja = new Stacja(ilosc_torow, ilosc_pociagow);
        for(int i = 0; i< ilosc_pociagow; i++) {
            new Pociag(i, 2000, Stacja).start();
        }
    }

}
