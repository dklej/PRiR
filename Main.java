package dk;

import java.util.Scanner;

public class Main {

    public static void main(String[] args) throws InterruptedException{
        double startFigury = 1, koniecFigury = 3, wynikKoncowy =0;
        int n;
        Scanner s = new Scanner(System.in);
        do {
            System.out.print("Podaj ilość n-wątków: ");
            n = s.nextInt();
        }
        while (n <= 0);

        double roznica = koniecFigury - startFigury;
        double sFi, kFi;

            System.out.print("Wybierz metode:  1. Trapezow 2. Prostokątów 3. Simpsona: ");
            int wybor = s.nextInt();
            switch (wybor) {
                case 1:
                    for (int i = 0; i < n; i++) {
                        if (i != 0)
                            sFi = startFigury + roznica / n * i;
                        else
                            sFi = startFigury + roznica / n * i;
                        kFi = startFigury + roznica / n * (i + 1);
                        M_trapezow watek = new M_trapezow(sFi, kFi);
                        watek.start();
                        watek.join();
                        wynikKoncowy += watek.wynik;
                    }
                    System.out.println(wynikKoncowy);
                    break;
                case 2:
                    for (int i = 0; i < n; i++) {
                        if (i != 0)
                            sFi = startFigury + roznica / n * i;
                        else
                            sFi = startFigury + roznica / n * i;
                        kFi = startFigury + roznica / n * (i + 1);
                        M_prostokatow watek = new M_prostokatow(sFi, kFi);
                        watek.start();
                        watek.join();
                        wynikKoncowy += watek.wynik;
                    }
                    System.out.println(wynikKoncowy);
                    break;
                case 3:
                    for (int i = 0; i < n; i++) {
                        if (i != 0)
                            sFi = startFigury + roznica / n * i;
                        else
                            sFi = startFigury + roznica / n * i;
                        kFi = startFigury + roznica / n * (i + 1);
                        M_Simpsona watek = new M_Simpsona(sFi, kFi);
                        watek.start();
                        watek.join();
                        wynikKoncowy += watek.suma;
                    }
                    System.out.println(wynikKoncowy);
                    break;
            }
        }

}

