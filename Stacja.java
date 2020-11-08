package dk;

public class Stacja {
    static int STACJA = 1;
    static int START = 2;
    static int KONIEC_LOTU = 4;
    int ilosc_pasow;
    int ilosc_zajetych_torow;
    int ilosc_pociagow;
    Stacja(int ilosc_torow, int ilosc_pociagow){
        this.ilosc_pasow = ilosc_torow;
        this.ilosc_pociagow = ilosc_pociagow;
        this.ilosc_zajetych_torow = 0;
    }
    int start(int numer){
        ilosc_zajetych_torow--;
        System.out.println("Odjazd pociągu "+numer);
        return START;
    }
    void odjazd_pociagu(){
        ilosc_pociagow--;
        System.out.println("ZABILEM");
        if(ilosc_pociagow ==ilosc_pasow) System.out.println("Ilosc samaoltow jaka sama jak pasow");
    }
    int wsiadka_pasazerow(){
        try{
            Thread.currentThread().sleep(100);
        }
        catch(Exception ie){
        }
        if(ilosc_zajetych_torow <ilosc_pasow){
            ilosc_zajetych_torow++;
            System.out.println("Wjazd na stację ");
            return STACJA;
        }
        else
        {return KONIEC_LOTU;}
    }

}
