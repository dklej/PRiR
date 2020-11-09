import java.awt.*;
import java.io.File;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.imageio.ImageIO;

public class Julia extends Thread {

    final static int n = 4096;
    final static int c = 50;
    static double R = 0.135;
    static double I = -0.701;
    static int[][] ustaw = new int[n][n];
    int art;
    public Julia(int art){
        this.art = art;
    }
    public static void main(String a[]) throws IOException, InterruptedException {
        Julia j1 = new Julia(0);
        Julia j2 = new Julia(1);
        Julia j3 = new Julia(2);
        Julia j4 = new Julia(3);
        Julia j5 = new Julia(4);
        j1.start();
        j2.start();
        j3.start();
        j4.start();
        j5.start();
        j1.join();
        j2.join();
        j3.join();
        j4.join();
        j5.join();
        System.out.println("Zakończono proces");
        BufferedImage img = new BufferedImage(n, n, BufferedImage.TYPE_INT_ARGB);
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                int k = ustaw[i][j];
                float level;
                if(k < c){
                    level = (float) k / c;
                }else{
                    level = 0; }
                Color c = new Color(0, level, 0);
                img.setRGB(i, j, c.getRGB()); } }
        ImageIO.write(img, "PNG", new File("wynik.png"));
    }

    public void run(){
        int begin = 0, end = 0;

        if(art == 0){
            begin = 0;
            end = (n/4) * 1; }
        else if (art == 1){
            begin = (n/ 4) * 1;
            end = (n / 4) * 2; }
        else if (art == 2){
            begin = (n/ 4) * 2;
            end = (n / 4) * 3; }
        else if (art == 3){
            begin = (n/ 4) * 3;
            end = (n/4) * 4; }
        else if (art == 4){
            begin = (n/ 4) * 4;
            end = n; }

        for (int i = begin; i < end; i++){
            for (int j = 0; j < n; j++){
                double cr = 1.5 * (i - n / 2) / (0.5 * 1 * n);
                double ci = (j - n / 2) / (0.5 * 1 * n);
                double zr = cr, zi = ci;
                int k = 0;
                while(k < c && zr * zr + zi * zi < 4.0){
                    double oldr = zr;
                    double oldi = zi;
                    zr = oldr * oldr - oldi * oldi + R;
                    zi = 2 * oldr * oldi + I;
                    k++; }
                ustaw[i][j] = k; } }
    }
}
