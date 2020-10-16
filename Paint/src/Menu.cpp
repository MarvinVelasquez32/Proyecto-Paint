#include "Menu.h"
#include "Allegro.h"
#define AN 680
#define AL 420

Menu::Menu()
{
 /*VACIO POR DEFECTO PARA CREAR UN OBJETO MENU Y USAR UNA FUNCION*/
}

int Menu::Mostrar_Menu(int n)
{
    int bucle_menu = 0;
    int Eleccion;

    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, AN, AL, 0, 0);

    BITMAP *buffer = create_bitmap(AN, AL);
    BITMAP *cursor = load_bmp("cursor-mano.bmp", NULL);
    BITMAP *menu = load_bmp("menu.bmp", NULL);
    BITMAP *menu1 = load_bmp("menu-1.bmp", NULL);
    BITMAP *menu2 = load_bmp("menu-2.bmp", NULL);
    BITMAP *menu3 = load_bmp("menu-3.bmp", NULL);

    /*---------------CREACION DE MENU PARA RESOLUCION DE LIENZO---------------*/
    while (!bucle_menu == 1)
    {
        if (mouse_x > 290 && mouse_x < 407 &&
        mouse_y > 177 && mouse_y < 212){
            blit( menu1, buffer, 0,0,0,0, AN, AL);

            if (mouse_b & 1)
            {
                Eleccion = 1;
                bucle_menu++;
            }

        } else if (mouse_x > 272 && mouse_x < 429 &&
        mouse_y > 235 && mouse_y < 270){
            blit( menu2, buffer, 0,0,0,0, AN, AL);

            if (mouse_b & 1)
            {
                Eleccion = 2;
                bucle_menu++;
            }

        } else if (mouse_x > 207 && mouse_x < 500 &&
        mouse_y > 292 && mouse_y < 326){
            blit( menu3, buffer, 0,0,0,0, AN, AL);

            if (mouse_b & 1)
            {
                Eleccion = 3;
                bucle_menu++;
            }

        } else blit( menu, buffer, 0,0,0,0, AN, AL);

        draw_sprite(buffer, cursor, mouse_x - 6, mouse_y - 2);

        blit(buffer, screen, 0, 0, 0, 0, AN, AL);
    }

    destroy_bitmap(menu);
    destroy_bitmap(menu1);
    destroy_bitmap(menu2);
    destroy_bitmap(menu3);
    destroy_bitmap(cursor);
    destroy_bitmap(buffer);


    /*---------------CREACION DE MENU PARA RESOLUCION DE LIENZO---------------*/
    return Eleccion;
}

