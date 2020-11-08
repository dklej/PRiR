package dk;

import java.util.Random;

public class Pociag extends Thread{
    //definicja stanu samolotu
    static int STACJA = 1;
    static int START = 2;
    static int TRASA = 3;
    static int KONIEC_PRZEJAZDU = 4;
    static int KATASTROFA = 5;
    static int ZALADUJ = 1000;
    static int REZERWA = 500;
    //zmienne pomocnicze
    int numer;
    int czas;
    int stan;
    Stacja l;
    Random rand;
    public Pociag(int numer, int czas, Stacja l){
        this.numer=numer;
        this.czas = czas;
        this.stan = TRASA;
        this.l=l;
        rand=new Random();
    }
    public void run(){
        while(true){
            if(stan== STACJA){
                if(rand.nextInt(2)==1){
                    stan = START;
                    czas = ZALADUJ;
                    System.out.println("Na stacji, niedługo ruszy " + numer);
                            stan=l.start(numer);
                }
                else{
                    System.out.println("Postoje sobie jeszcze troche, PKP w końcu");
                }
            }
            else if(stan==START){
                System.out.println("CIU CIU ODJAZD! "+numer);
                stan= TRASA;
            }
            else if(stan== TRASA){
                czas -= rand.nextInt(1000);
                System.out.println("Pociąg ICC " + numer + " w trasie");
                if(czas <=REZERWA){
                    stan = KONIEC_PRZEJAZDU;
                }
                else try{
                    Thread.sleep(rand.nextInt(500));
                }
                catch (Exception e){}
            }
            else if(stan==KONIEC_PRZEJAZDU){
                System.out.println("Pociąg "+numer+" prosi o wjazd na stację, czas do przyjazdu punktualnie - "+ czas);
                stan=l.wsiadka_pasazerow();
                if(stan==KONIEC_PRZEJAZDU){
                    czas -= rand.nextInt(1000);
                    System.out.println("REZERWA na kawkę w WARSIE "+ czas);
                    if(czas <=0) stan=KATASTROFA;
                }
            }
            else if(stan==KATASTROFA){
                System.out.println("PKP ICC przeprasza za O P Ó Ź N I E N I E znowu...    "+numer);
                l.odjazd_pociagu();
            }
        }}
}
