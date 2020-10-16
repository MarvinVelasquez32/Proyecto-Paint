#include <allegro.h> /*INSTALAMOS LA LIBRERIA*/
#include <math.h> /*PARA SQRT()*/
#include "Menu.h"
#include "Linea.h"
#include "Circulo.h"
#include "Rectangulo.h"
#include "Triangulo.h"
#include "Pentagono.h"
#include "Curva.h"

int ANCHO;
int ALTO;

bool Click_Presionado = false;
int Herramienta = 4;
int Codigo_De_Color  = 0x000000;
int colorR = 255;
int colorG = 255;
int colorB = 255;
int Anclaje_x, Anclaje_y;
bool Imprimir = false;
int Eleccion_De_Resolucion;

BITMAP *buffer;
BITMAP *dibujo;
BITMAP *Barra_De_Botones;
BITMAP *Indicador_De_Color;
BITMAP *Lapiz;
BITMAP *Borrador;
BITMAP *Cubeta;
BITMAP *Escoba;
BITMAP *Cursor_Figura;

PALETTE pal;

bool Cordenadas_De_Barra_De_Botones(){
    return (mouse_x > 0 && mouse_x < 384 && mouse_y > 0 && mouse_y < 64);
};


void Elegir_Herramienta(){

    //accion borrar todo
    if (mouse_x > 0 && mouse_x < 30 && mouse_y > 0 && mouse_y < 30){
        rect( buffer, 2,2,29,29, 0x0067FF );
        if ( mouse_b&1 ) Herramienta = 1 ;
    }

    //accion borrar
    if (mouse_x > 33 && mouse_x < 64 && mouse_y > 0 && mouse_y < 31){
        rect( buffer, 34,2,60,29, 0x0067FF );
        if ( mouse_b&1 ) Herramienta = 2;
    }

    //accion cubeta
    if (mouse_x > 0 && mouse_x < 31 && mouse_y > 32 && mouse_y < 63){
        rect( buffer, 3,35,28,60, 0x0067FF );
        if ( mouse_b&1 ) Herramienta = 3;
    }

    //accion lapiz
    if (mouse_x > 33 && mouse_x < 63 && mouse_y > 31 && mouse_y < 63){
        rect( buffer, 35,35,60,60, 0x0067FF );
        if ( mouse_b&1 ) Herramienta = 4;
    }

    //accion boton rojo 1
    if (mouse_x > 64 && mouse_x < 89 && mouse_y > 1 && mouse_y < 21 ){
        rect( buffer, 64,0,89,21, 0x0067FF );
        if ( colorR > 0 ) colorR--;
    }

    //accion boton verde 1
    if (mouse_x > 64 && mouse_x < 89 && mouse_y > 22 && mouse_y < 41 ){
        rect( buffer, 64,21,89,42, 0x0067FF );
        if ( colorG > 0 ) colorG--;
    }

    //accion boton azul 1
    if (mouse_x > 64 && mouse_x < 89 && mouse_y > 43 && mouse_y < 63 ){
        rect( buffer, 64,42,89,63, 0x0067FF );
        if ( colorB > 0 ) colorB--;
    }

    //accion boton rojo 2
    if (mouse_x > 168 && mouse_x < 191 && mouse_y > 1 && mouse_y < 20 ){
        rect( buffer, 166,0,191,21, 0x0067FF );
        if ( colorR < 255 ) colorR++;
    }

    //accion boton verde 2
    if (mouse_x > 168 && mouse_x < 191 && mouse_y > 22 && mouse_y < 41 ){
        rect( buffer, 166,21,191,42, 0x0067FF );
        if ( colorG < 255 ) colorG++;
    }

    //accion boton azul 2
    if (mouse_x > 168 && mouse_x < 191 && mouse_y > 43 && mouse_y < 63 ){
        rect( buffer, 166,42,191,63, 0x0067FF );
        if ( colorB < 255 ) colorB++;
    }


    //Boton grande para seleccionar el nuevo color
    if ( mouse_x > 194 && mouse_x < 253 && mouse_y > 2   && mouse_y < 61 ){
        Codigo_De_Color = makecol(colorR,colorG,colorB);
    }


    //Boton para guardar el buffer en una foto
    if (mouse_x > 259 && mouse_x < 284 && mouse_y > 3   && mouse_y < 28 ){
        rect( buffer, 259,3,284,28, 0x0067FF );
        // guarda imagen
        get_palette(pal);
        save_bitmap("Mi_Primer_Dibujo.bmp", dibujo, pal);
    }

    //Boton de gotero
    if (mouse_x > 259 && mouse_x < 284 && mouse_y > 35 && mouse_y < 60){
        rect( buffer, 259,35,284,60, 0x0067FF );
        Herramienta = 5;
    }


    //Boton de linea
    if (mouse_x > 291 && mouse_x < 316 && mouse_y > 3   && mouse_y < 28 ){
        rect( buffer, 291,3,316,28, 0x0067FF );
        Herramienta = 6;
    }

    //Boton de circulo
    if (mouse_x > 291 && mouse_x < 316 && mouse_y > 35 && mouse_y < 60){
        rect( buffer, 291,35,316,60, 0x0067FF );
        Herramienta = 7;
    }

    //Boton de cuadrado
    if (mouse_x > 323 && mouse_x < 348 && mouse_y > 3   && mouse_y < 28 ){
        rect( buffer, 323,3,348,28, 0x0067FF );
        Herramienta = 8;
    }

    //Boton de Triangulo
    if (mouse_x > 323 && mouse_x < 348 && mouse_y > 35 && mouse_y < 60){
        rect( buffer, 323,35,348,60, 0x0067FF );
        Herramienta = 9;
    }

    //Boton de Curva
    if (mouse_x > 355 && mouse_x < 380 && mouse_y > 3   && mouse_y < 28 ){
     rect( buffer, 355,3,380,28, 0x0067FF );
        Herramienta = 10;
    }

    //Boton de Pentagono
   if (mouse_x > 355 && mouse_x < 380 && mouse_y > 35   && mouse_y < 60 ){
        rect( buffer, 355,35,380,60, 0x0067FF);
        Herramienta = 11;
    }

};


void Imprimir_En_Dibujo(){
    //Guarda la variable radio que generamos
    int Radio;

    switch(Herramienta){

        case 6:
           // LINEA
           if (Imprimir == true){
                Imprimir = false;

                /*-----------------------------CREAR OBJETO LINEA------------------------------*/
                Linea Objeto_Linea = Linea(Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                /*-----------------------------CREAR OBJETO LINEA------------------------------*/

                /*-----------------------------IMPRIMIR PROCESOS LINEA------------------------------*/
                line(dibujo, Objeto_Linea.An_x, Objeto_Linea.An_y, Objeto_Linea.M_x, Objeto_Linea.M_y,
                Objeto_Linea.Codigo_De_Color);
                /*-----------------------------IMPRIMIR PROCESOS LINEA------------------------------*/
            }

        break;

        case 7:
           // CIRCULO
           if (Imprimir == true) {
                Imprimir = false;

                int Radio = int(sqrt( ((Anclaje_x-mouse_x)*(Anclaje_x-mouse_x)) + ((Anclaje_y-mouse_y)*(Anclaje_y-mouse_y)) ));
                circle(dibujo, Anclaje_x, Anclaje_y, Radio, Codigo_De_Color);
            }

        break;

        case 8:
           // RECTANGULO
           if (Imprimir == true) {
                Imprimir = false;

                rect( dibujo, Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
            }

        break;

        case 9:
           // TRIANGULO
           if (Imprimir == true) {
                Imprimir = false;

                line(dibujo, Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                line(dibujo, Anclaje_x, Anclaje_y, Anclaje_x + (mouse_y-Anclaje_y), Anclaje_y, Codigo_De_Color);
                line(dibujo, mouse_x, mouse_y, Anclaje_x + (mouse_y-Anclaje_y), Anclaje_y, Codigo_De_Color);
            }

        break;

        case 10:
            //CURVA
           if (Imprimir == true){
                Imprimir = false;

                int Radio_curva = int (sqrt( ((Anclaje_x-mouse_x)*(Anclaje_x-mouse_x)) + ((Anclaje_y-mouse_y)*(Anclaje_y-mouse_y)) ));
                arc(dibujo, Anclaje_x, Anclaje_y, itofix ( 20 ) , itofix ( 108 ) , Radio_curva, Codigo_De_Color);
          };

        break;

        case 11:
            //PENTAGONO
           if (Imprimir == true){
                Imprimir = false;

                /*======================PRIMERA LINEA DEL PENTAGONO======================*/
                line(dibujo, Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                /*======================PRIMERA LINEA DEL PENTAGONO======================*/

                /*======================SEGUNDA LINEA DEL PENTAGONO======================*/
                line(dibujo, Anclaje_x, Anclaje_y,
                Anclaje_x - ((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x)),
                Anclaje_y, Codigo_De_Color);
                /*======================SEGUNDA LINEA DEL PENTAGONO======================*/

                /*======================TERCERA LINEA DEL PENTAGONO======================*/
                line(dibujo, Anclaje_x - ((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x)), Anclaje_y,
                Anclaje_x - (((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x))+(mouse_x-Anclaje_x)),
                Anclaje_y + (mouse_y-Anclaje_y), Codigo_De_Color);
                /*======================SEGUNDA LINEA DEL PENTAGONO======================*/

                /*======================CUARTA LINEA DEL PENTAGONO======================*/
                line(dibujo,Anclaje_x - (((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x))
                +(mouse_x-Anclaje_x)), Anclaje_y + (mouse_y-Anclaje_y),
                mouse_x - (((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x))
                +(mouse_x-Anclaje_x))+(((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x))/2),
                mouse_y + (mouse_y-Anclaje_y), Codigo_De_Color);
                /*======================CUARTA LINEA DEL PENTAGONO======================*/

                /*======================QUINTA LINEA DEL PENTAGONO======================*/
                line(dibujo, mouse_x - (((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x))
                +(mouse_x-Anclaje_x))+(((Anclaje_y-mouse_y)-(Anclaje_x-mouse_x))/2),
                mouse_y + (mouse_y-Anclaje_y),mouse_x, mouse_y, Codigo_De_Color);
                /*======================QUINTA LINEA DEL PENTAGONO======================*/
          };

        break;

    };
}


void Imprimir_Procesos(){

    switch(Herramienta){

     /*-----------------LIMPIAMOS LA PANTALLA CON EL COLOR BLANCO--------------------*/
        case 1:
            clear_to_color(dibujo, 0xFFFFFF);
        break;
     /*-----------------LIMPIAMOS LA PANTALLA CON EL COLOR BLANCO--------------------*/

     /*-----------------HACEMOS QUE NUESTRO CURSOR BORRE--------------------*/
        case 2:
            putpixel(dibujo, mouse_x, mouse_y, 0xFFFFFF);

            putpixel(dibujo, mouse_x-1, mouse_y, 0xFFFFFF);
            putpixel(dibujo, mouse_x-1, mouse_y-1, 0xFFFFFF);
            putpixel(dibujo, mouse_x, mouse_y-1, 0xFFFFFF);
            putpixel(dibujo, mouse_x+1, mouse_y-1, 0xFFFFFF);
            putpixel(dibujo, mouse_x+1, mouse_y, 0xFFFFFF);
            putpixel(dibujo, mouse_x+1, mouse_y+1, 0xFFFFFF);
            putpixel(dibujo, mouse_x, mouse_y+1, 0xFFFFFF);
            putpixel(dibujo, mouse_x-1, mouse_y+1, 0xFFFFFF);
            putpixel(dibujo, mouse_x, mouse_y, 0xFFFFFF);
            putpixel(dibujo, mouse_x, mouse_y, 0xFFFFFF);

        break;
     /*-----------------HACEMOS QUE NUESTRO CURSOR BORRE--------------------*/

     /*-----------------LA FUNCION CUBETA--------------------*/
        case 3:
            floodfill(dibujo, mouse_x, mouse_y, Codigo_De_Color);
        break;
     /*-----------------LA FUNCION CUBETA--------------------*/

     /*-----------------HACEMOS QUE EL CURSOR PINTE--------------------*/
        case 4:
            putpixel(dibujo, mouse_x, mouse_y, Codigo_De_Color);

            putpixel(dibujo, mouse_x-1, mouse_y, Codigo_De_Color);
            putpixel(dibujo, mouse_x-1, mouse_y-1, Codigo_De_Color);
            putpixel(dibujo, mouse_x, mouse_y-1, Codigo_De_Color);
            putpixel(dibujo, mouse_x+1, mouse_y-1, Codigo_De_Color);
            putpixel(dibujo, mouse_x+1, mouse_y, Codigo_De_Color);
            putpixel(dibujo, mouse_x+1, mouse_y+1, Codigo_De_Color);
            putpixel(dibujo, mouse_x, mouse_y+1, Codigo_De_Color);
            putpixel(dibujo, mouse_x-1, mouse_y+1, Codigo_De_Color);
            putpixel(dibujo, mouse_x, mouse_y, Codigo_De_Color);
            putpixel(dibujo, mouse_x, mouse_y, Codigo_De_Color);
        break;
     /*-----------------HACEMOS QUE EL CURSOR PINTE--------------------*/

     /*---------------------OPCION DE GOTERO---------------------*/
        case 5:
            Codigo_De_Color = getpixel(dibujo, mouse_x, mouse_y);
        break;
     /*---------------------OPCION DE GOTERO---------------------*/

     /*---------------------HACER UNA LINEA---------------------*/
        case 6:

            if (Imprimir == false ){
                Anclaje_x = mouse_x;
                Anclaje_y = mouse_y;
                Imprimir = true;
            }

            if (Imprimir == true) {
            /*-----------------------------CREAR OBJETO LINEA------------------------------*/
            Linea Objeto_Linea = Linea(Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
            /*-----------------------------CREAR OBJETO LINEA------------------------------*/

            /*-----------------------------IMPRIMIR PROCESOS LINEA------------------------------*/
            line(buffer, Objeto_Linea.An_x, Objeto_Linea.An_y, Objeto_Linea.M_x, Objeto_Linea.M_y,
            Objeto_Linea.Codigo_De_Color);
            /*-----------------------------IMPRIMIR PROCESOS LINEA------------------------------*/
            }

        break;
     /*---------------------HACER UNA LINEA---------------------*/

     /*---------------------HACER UN CIRCULO---------------------*/
        case 7:

            if ( Imprimir == false ){
                Anclaje_x = mouse_x;
                Anclaje_y = mouse_y;
                Imprimir = true;
            }

            if ( Imprimir == true ) {

                /*-----------------------------CREAR OBJETO CIRCULO------------------------------*/
                Circulo Objeto_Circulo = Circulo(Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                /*-----------------------------CREAR OBJETO CIRCULO------------------------------*/

                /*-----------------------------CREAR EL RADIO PROPORCIONAL AL MAUS------------------------------*/
                int Radio = int (sqrt( ((Objeto_Circulo.An_x-Objeto_Circulo.M_x)*(Objeto_Circulo.An_x-Objeto_Circulo.M_x))
                + ((Objeto_Circulo.An_y-Objeto_Circulo.M_y)*(Objeto_Circulo.An_y-Objeto_Circulo.M_y)) ));
                /*-----------------------------CREAR EL RADIO PROPORCIONAL AL MAUS------------------------------*/

                /*-----------------------------IMPPRIMIR PROCESOS CIRCULO------------------------------*/
                circle(buffer, Objeto_Circulo.An_x, Objeto_Circulo.An_y, Radio, Objeto_Circulo.Codigo_De_Color);
                /*-----------------------------IMPPRIMIR PROCESOS CIRCULO------------------------------*/
            }

        break;
     /*---------------------HACER UN CIRCULO---------------------*/

     /*---------------------HACER UN RECTANGULO---------------------*/
        case 8:

            if ( Imprimir == false ){
                Anclaje_x = mouse_x;
                Anclaje_y = mouse_y;
                Imprimir = true;
            }

            if ( Imprimir == true ) {
                /*-----------------------------CREAR OBJETO RECTANGULO------------------------------*/
                Rectangulo Objeto_Rectangulo = Rectangulo(Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                /*-----------------------------CREAR OBJETO RECTANGULO------------------------------*/

                /*-----------------------------IMPRIMIR PROCESOS RECTANGULO------------------------------*/
                rect (buffer, Objeto_Rectangulo.An_x, Objeto_Rectangulo.An_y, Objeto_Rectangulo.M_x,
                Objeto_Rectangulo.M_y, Objeto_Rectangulo.Codigo_De_Color);
                /*-----------------------------IMPRIMIR PROCESOS RECTANGULO------------------------------*/
            }

        break;
     /*---------------------HACER UN RECTANGULO---------------------*/

     /*---------------------HACER UNA TRIANGULO---------------------*/
        case 9:

            if ( Imprimir == false ){
                Anclaje_x = mouse_x;
                Anclaje_y = mouse_y;
                Imprimir = true;
            }

            if ( Imprimir == true ) {

                /*-----------------------------CREAR OBJETO RECTANGULO------------------------------*/
                Triangulo Objeto_Triangulo = Triangulo(Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                /*-----------------------------CREAR OBJETO RECTANGULO------------------------------*/

                /*---------------------------------------PRIMERA LINEA---------------------------------------*/
                line(buffer, Objeto_Triangulo.An_x, Objeto_Triangulo.An_y, Objeto_Triangulo.M_x,
                Objeto_Triangulo.M_y, Objeto_Triangulo.Codigo_De_Color);
                /*---------------------------------------PRIMERA LINEA---------------------------------------*/
                /*---------------------------------------SEGINDA LINEA---------------------------------------*/
                line(buffer, Objeto_Triangulo.An_x, Objeto_Triangulo.An_y, Objeto_Triangulo.An_x
                + (Objeto_Triangulo.M_y-Objeto_Triangulo.An_y), Objeto_Triangulo.An_y, Objeto_Triangulo.Codigo_De_Color);
                /*---------------------------------------SEGUNDA LINEA---------------------------------------*/
                /*---------------------------------------TERCERA LINEA---------------------------------------*/
                line(buffer, Objeto_Triangulo.M_x, Objeto_Triangulo.M_y, Objeto_Triangulo.An_x
                + (Objeto_Triangulo.M_y-Objeto_Triangulo.An_y), Objeto_Triangulo.An_y, Objeto_Triangulo.Codigo_De_Color);
                /*---------------------------------------TERCERA LINEA---------------------------------------*/
            }

        break;
     /*---------------------HACER UNA TRANGULO---------------------*/

     /*---------------------HACER UNA CURVA---------------------*/
       case 10:

            if ( Imprimir == false ){
                Anclaje_x = mouse_x;
                Anclaje_y = mouse_y;
                Imprimir = true;
            }

            if ( Imprimir == true ) {

                /*-----------------------------CREAR OBJETO CURVA------------------------------*/
                Curva Objeto_Curva = Curva(Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                /*-----------------------------CREAR OBJETO CURVA------------------------------*/

                /*-----------------------------CREAR LA CURVATURA PROPORCIONAL AL MAUS------------------------------*/
                int Radio_curva = int (sqrt( ((Objeto_Curva.An_x-Objeto_Curva.M_x)*(Objeto_Curva.An_x-Objeto_Curva.M_x))
                + ((Objeto_Curva.An_y-Objeto_Curva.M_y)*(Objeto_Curva.An_y-Objeto_Curva.M_y)) ));
                /*-----------------------------CREAR LA CURVATURA PROPORCIONAL AL MAUS------------------------------*/

                /*-----------------------------IMPRIMIR PROCESOS CURVA------------------------------*/
                arc(buffer, Objeto_Curva.An_x, Objeto_Curva.An_y, itofix(20), itofix(108), Radio_curva, Codigo_De_Color);
                /*-----------------------------IMPRIMIR PROCESOS CURVA------------------------------*/
            }

        break;
     /*---------------------HACER UNA CURVA---------------------*/

     /*---------------------HACER UNA PENTAGONO---------------------*/
       case 11:

            if ( Imprimir == false ){
                Anclaje_x = mouse_x;
                Anclaje_y = mouse_y;
                Imprimir = true;
            }

            if ( Imprimir == true ) {

                /*-----------------------------CREAR OBJETO RECTANGULO------------------------------*/
                Pentagono Objeto_Pentagono = Pentagono(Anclaje_x, Anclaje_y, mouse_x, mouse_y, Codigo_De_Color);
                /*-----------------------------CREAR OBJETO RECTANGULO------------------------------*/

                /*======================PRIMERA LINEA DEL PENTAGONO======================*/
                line(buffer, Objeto_Pentagono.An_x, Objeto_Pentagono.An_y, Objeto_Pentagono.M_x,
                Objeto_Pentagono.M_y, Objeto_Pentagono.Codigo_De_Color);
                /*======================PRIMERA LINEA DEL PENTAGONO======================*/

                /*======================SEGUNDA LINEA DEL PENTAGONO======================*/
                line(buffer, Objeto_Pentagono.An_x, Objeto_Pentagono.An_y,
                Objeto_Pentagono.An_x - ((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)
                -(Objeto_Pentagono.An_x-Objeto_Pentagono.M_x)),
                Objeto_Pentagono.An_y, Objeto_Pentagono.Codigo_De_Color);
                /*======================SEGUNDA LINEA DEL PENTAGONO======================*/

                /*======================TERCERA LINEA DEL PENTAGONO======================*/
                line(buffer, Objeto_Pentagono.An_x - ((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)
                -(Objeto_Pentagono.An_x-Objeto_Pentagono.M_x)), Objeto_Pentagono.An_y,
                Objeto_Pentagono.An_x - (((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)
                -(Objeto_Pentagono.An_x-Objeto_Pentagono.M_x))+(Objeto_Pentagono.M_x-Objeto_Pentagono.An_x)),
                Objeto_Pentagono.An_y + (Objeto_Pentagono.M_y-Objeto_Pentagono.An_y),
                Objeto_Pentagono.Codigo_De_Color);
                /*======================SEGUNDA LINEA DEL PENTAGONO======================*/

                /*======================CUARTA LINEA DEL PENTAGONO======================*/
                line(buffer,Objeto_Pentagono.An_x - (((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)
                -(Objeto_Pentagono.An_x-Objeto_Pentagono.M_x))
                +(Objeto_Pentagono.M_x-Objeto_Pentagono.An_x)), Objeto_Pentagono.An_y +
                (Objeto_Pentagono.M_y-Objeto_Pentagono.An_y),
                Objeto_Pentagono.M_x - (((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)
                -(Objeto_Pentagono.An_x-Objeto_Pentagono.M_x))
                +(Objeto_Pentagono.M_x-Objeto_Pentagono.An_x))+
                (((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)-
                (Objeto_Pentagono.An_x-Objeto_Pentagono.M_x))/2),
                Objeto_Pentagono.M_y + (Objeto_Pentagono.M_y-Objeto_Pentagono.An_y),
                Objeto_Pentagono.Codigo_De_Color);
                /*======================CUARTA LINEA DEL PENTAGONO======================*/

                /*======================QUINTA LINEA DEL PENTAGONO======================*/
                line(buffer, Objeto_Pentagono.M_x - (((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)
                -(Objeto_Pentagono.An_x-Objeto_Pentagono.M_x))
                +(Objeto_Pentagono.M_x-Objeto_Pentagono.An_x))+
                (((Objeto_Pentagono.An_y-Objeto_Pentagono.M_y)
                -(Objeto_Pentagono.An_x-Objeto_Pentagono.M_x))/2),
                Objeto_Pentagono.M_y + (Objeto_Pentagono.M_y-Objeto_Pentagono.An_y),
                Objeto_Pentagono.M_x, Objeto_Pentagono.M_y, Objeto_Pentagono.Codigo_De_Color);
                /*======================QUINTA LINEA DEL PENTAGONO======================*/
            }

        break;
     /*---------------------HACER UNA PENTAGONO---------------------*/

    }
}


void Boton_izquierdo(){

    if (Cordenadas_De_Barra_De_Botones()){
        Elegir_Herramienta();
    }else{
        Imprimir_Procesos();
    }

}


void Colocar_Barra_De_Botones(){

    /*----------------------MODIFICA EL TAMANIO MENU COLORES----------------------*/
    rectfill(buffer, 192, 1, 255, 63, makecol(colorR,colorG,colorB));
    /*----------------------MODIFICA EL TAMANIO MENU COLORES----------------------*/

    /*-----------------MODIFICA EL TAMANIO COLOCA LA CALCOMANIA MENU------------------*/
    masked_blit(Barra_De_Botones, buffer, 0, 0, 0, 0, 384, 64);
    /*-----------------MODIFICA EL TAMANIO COLOCA LA CALCOMANIA MENU------------------*/

    /*-----------------------MODIFICA LA SELECCION DE COLOR-----------------------*/
    rectfill(buffer, 208,15,225,33, Codigo_De_Color);
    /*-----------------------MODIFICA LA SELECCION DE COLOR-----------------------*/

    /*------------------MODIFICA LA LONGITUD DE EL CAMBIO DE COLOR------------------*/
    int Rango_De_Color;

    Rango_De_Color = int (colorR*73 / 255 );
    blit(Indicador_De_Color, buffer, 0, 0, 90+Rango_De_Color,1,3,20);

    Rango_De_Color = int (colorG*73 / 255 );
    blit(Indicador_De_Color, buffer, 0, 0, 90+Rango_De_Color,22,3,20);

    Rango_De_Color = int (colorB*73 / 255 );
    blit(Indicador_De_Color, buffer, 0, 0, 90+Rango_De_Color,44,3,20);
    /*------------------MODIFICA LA LONGITUD DE EL CAMBIO DE COLOR------------------*/
}


int main()
{
    allegro_init();
    install_keyboard();
    install_mouse();

    Menu Pantalla_De_Menu = Menu();
    Eleccion_De_Resolucion = Pantalla_De_Menu.Mostrar_Menu(0);

    if (Eleccion_De_Resolucion == 1)
    {
        ANCHO = 640;
        ALTO = 480;
    } else if (Eleccion_De_Resolucion == 2)
    {
        ANCHO = 1024;
        ALTO = 576;
    }else if (Eleccion_De_Resolucion == 3)
    {
        ANCHO = 1360;
        ALTO = 768;
    }

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, ANCHO, ALTO, 0, 0);

    Barra_De_Botones/*===*/= load_bmp("Barra_De_Botones.bmp",NULL);
    Indicador_De_Color/*=*/= load_bmp("Indicador_De_Color.bmp",NULL);
    Lapiz/*==============*/= load_bmp("Lapiz.bmp", NULL);
    Borrador/*===========*/= load_bmp("Borrador.bmp", NULL);
    Cubeta/*=============*/= load_bmp("Cubeta.bmp", NULL);
    Escoba/*=============*/= load_bmp("Escoba.bmp", NULL);
    Cursor_Figura/*======*/= load_bmp("Cursor_Figura.bmp", NULL);

    buffer = create_bitmap(ANCHO, ALTO);
    dibujo = create_bitmap(ANCHO, ALTO);

    clear_to_color(buffer, 0xFFFFFF);
    clear_to_color(dibujo, 0xFFFFFF);

    while( !key[KEY_ESC] ){

        blit(dibujo, buffer, 0,0,0,0, ANCHO, ALTO);
        Colocar_Barra_De_Botones();

        /*==================LE DAMOS IMAGEN AL CURSOR==================*/
        if (Herramienta == 1){
            draw_sprite(buffer, Escoba, mouse_x - 3, mouse_y - 21);
        }else if (Herramienta == 2){
            draw_sprite(buffer, Borrador, mouse_x - 4, mouse_y - 17);
        }else if (Herramienta == 3){
            draw_sprite(buffer, Cubeta, mouse_x - 3, mouse_y - 15);
        }else if (Herramienta == 4){
            draw_sprite(buffer, Lapiz, mouse_x, mouse_y - 20);
        }else{
            draw_sprite(buffer, Cursor_Figura, mouse_x - 11, mouse_y - 12);
        }
        /*==================LE DAMOS IMAGEN AL CURSOR==================*/


        /*--------------VERIFICAMOS EL BOTON PARA IMPRIMIR RESULTADOS--------------*/
        if (Click_Presionado == true) Imprimir_En_Dibujo();
        /*--------------VERIFICAMOS EL BOTON PARA IMPRIMIR RESULTADOS--------------*/


        /*--------------------SELECCIONAMOS NUESTRA HERRAMIENTA--------------------*/
        if(mouse_b & 1){
            Click_Presionado = false;
            Boton_izquierdo();
        }else{
            Click_Presionado = true;
        }
        /*--------------------SELECCIONAMOS NUESTRA HERRAMIENTA--------------------*/

        blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
    }

    destroy_bitmap(Barra_De_Botones);
    destroy_bitmap(dibujo);
    destroy_bitmap(buffer);
    destroy_bitmap(Indicador_De_Color);
    destroy_bitmap(Lapiz);
    destroy_bitmap(Borrador);
    destroy_bitmap(Cubeta);
    destroy_bitmap(Escoba);
    destroy_bitmap(Cursor_Figura);

    return 0;
}

END_OF_MAIN();


