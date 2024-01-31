#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtkx.h>
#include <math.h>
#include <ctype.h>
#include<pthread.h>



GtkBuilder* builder;

GtkWidget* GTK_Window;
GtkWidget* Main_Window;
GtkWidget* Back_Ground_Wall_Paper;
GtkWidget* shutdownImage;
GtkWidget* Clock_Widget;
GtkWidget* quitButton;

GtkWidget*  calImage;
GtkWidget*  gameImage;
GtkWidget*  conversionImage;
GtkWidget*  songImage;
GtkWidget*  sys_timeImage;
GtkWidget*  passImage;
GtkWidget*  facImage;
GtkWidget*  palindromeImage;
GtkWidget*  primeImage;
GtkWidget*  notepadImage;
GtkWidget*  bubbleImage;
GtkWidget*  armstrongImage;
GtkWidget*  fibImage;
GtkWidget*  terminalImage;

GtkWidget*  calButton;
GtkWidget*  gameButton;
GtkWidget*  conversionButton;
GtkWidget*  songButton;
GtkWidget*  sys_timeButton;
GtkWidget*  passButton;
GtkWidget*  facButton;
GtkWidget*  palindromeButton;
GtkWidget*  primeButton;
GtkWidget*  notepadButton;
GtkWidget*  bubbleButton;
GtkWidget*  armstrongButton;
GtkWidget*  fibButton;
GtkWidget*  terminalButton;

Bool pressed = False;
char *current_time;

char* exec(const char* cmd)
{
    FILE *fp;
    char result[1000];
    fp=popen(cmd, "r");
    fgets(result,sizeof(result),fp);
    pclose(fp);
    char* result2 = result;
    return strdup(result2);
}

void* makeTerminal(void* args)
{
    char* cmd = (char *)args;
    pthread_detach(pthread_self());
    system(args);
}

void makeNewTerminal(char* cmd)
{
    pthread_t id;

  	pthread_create(&id,NULL,makeTerminal, (void *)cmd);
}


void* update_time(void*args)
{
    pthread_detach(pthread_self());
    while(1)
    {
        current_time = exec("date +%r");
        gtk_label_set_text(GTK_LABEL(Clock_Widget), current_time);
        sleep(1);
    }
}

void quit_pressed(GtkButton *button)
{
    gtk_main_quit();
}

void cal_pressed(GtkButton * button)
{
    if(pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run calculator");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}

void game_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run num_guess_game");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void conversion_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run conversion");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void song_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run song");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void sys_time_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run sys_time");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void pass_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run password_setting");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void fac_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run factorial");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void palindrome_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run palindrome");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void prime_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run prime");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void notepad_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run os_notepad");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void bubble_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run bubblesort");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void armstrong_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run armstrong");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}
void fib_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS run fibonacci");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}

void terminal_pressed(GtkButton * button)
{
    if (pressed == False)
    {
        makeNewTerminal("alacritty -e ./FantasyOS");
        pressed = True;
    }
    else
    {
        pressed = False;
    }
}



int main(int argc, char *argv[])
{
	current_time = malloc(1000);
	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_file ("frontend.glade");
	GTK_Window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
	g_signal_connect(GTK_Window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

	Main_Window = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
	Back_Ground_Wall_Paper = GTK_WIDGET(gtk_builder_get_object(builder, "image"));
	
	quitButton = GTK_WIDGET(gtk_builder_get_object(builder, "shutdown"));
	Clock_Widget = GTK_WIDGET(gtk_builder_get_object(builder, "Clock_Widget"));


    calImage = GTK_WIDGET(gtk_builder_get_object(builder, "cal"));
    gameImage = GTK_WIDGET(gtk_builder_get_object(builder, "game"));
    conversionImage = GTK_WIDGET(gtk_builder_get_object(builder, "conversion"));
    songImage = GTK_WIDGET(gtk_builder_get_object(builder, "song"));
    sys_timeImage = GTK_WIDGET(gtk_builder_get_object(builder, "sys_time"));
    passImage = GTK_WIDGET(gtk_builder_get_object(builder, "pass"));
    facImage = GTK_WIDGET(gtk_builder_get_object(builder, "fac"));
    palindromeImage = GTK_WIDGET(gtk_builder_get_object(builder, "palindrome"));
    primeImage = GTK_WIDGET(gtk_builder_get_object(builder, "prime"));
    notepadImage = GTK_WIDGET(gtk_builder_get_object(builder, "notepad"));
    bubbleImage = GTK_WIDGET(gtk_builder_get_object(builder, "bubble"));
    armstrongImage = GTK_WIDGET(gtk_builder_get_object(builder, "armstrong"));
    fibImage = GTK_WIDGET(gtk_builder_get_object(builder, "fib"));
    terminalImage = GTK_WIDGET(gtk_builder_get_object(builder, "terminal"));


    calButton = GTK_WIDGET(gtk_builder_get_object(builder, "cal_button"));
    gameButton = GTK_WIDGET(gtk_builder_get_object(builder, "game_button"));
    conversionButton = GTK_WIDGET(gtk_builder_get_object(builder, "conversion_button"));
    songButton = GTK_WIDGET(gtk_builder_get_object(builder, "song_button"));
    sys_timeButton = GTK_WIDGET(gtk_builder_get_object(builder, "sys_time_button"));
    passButton = GTK_WIDGET(gtk_builder_get_object(builder, "pass_button"));
    facButton = GTK_WIDGET(gtk_builder_get_object(builder, "fac_button"));
    palindromeButton = GTK_WIDGET(gtk_builder_get_object(builder, "palindrome_button"));
    primeButton = GTK_WIDGET(gtk_builder_get_object(builder, "prime_button"));
    notepadButton = GTK_WIDGET(gtk_builder_get_object(builder, "notepad_button"));
    bubbleButton = GTK_WIDGET(gtk_builder_get_object(builder, "bubble_button"));
    armstrongButton = GTK_WIDGET(gtk_builder_get_object(builder, "armstrong_button"));
    fibButton = GTK_WIDGET(gtk_builder_get_object(builder, "fib_button"));
    terminalButton = GTK_WIDGET(gtk_builder_get_object(builder, "terminal_button"));

    g_signal_connect(G_OBJECT(quitButton), "clicked",G_CALLBACK(quit_pressed),NULL);

    g_signal_connect(G_OBJECT(calButton), "clicked",G_CALLBACK(cal_pressed),NULL);
    g_signal_connect(G_OBJECT(gameButton), "clicked",G_CALLBACK(game_pressed),NULL);
    g_signal_connect(G_OBJECT(conversionButton), "clicked",G_CALLBACK(conversion_pressed),NULL);
    g_signal_connect(G_OBJECT(songButton), "clicked",G_CALLBACK(song_pressed),NULL);
    g_signal_connect(G_OBJECT(sys_timeButton), "clicked",G_CALLBACK(sys_time_pressed),NULL);
    g_signal_connect(G_OBJECT(passButton), "clicked",G_CALLBACK(pass_pressed),NULL);
    g_signal_connect(G_OBJECT(facButton), "clicked",G_CALLBACK(fac_pressed),NULL);
    g_signal_connect(G_OBJECT(palindromeButton), "clicked",G_CALLBACK(palindrome_pressed),NULL);
    g_signal_connect(G_OBJECT(primeButton), "clicked",G_CALLBACK(prime_pressed),NULL);
    g_signal_connect(G_OBJECT(notepadButton), "clicked",G_CALLBACK(notepad_pressed),NULL);
    g_signal_connect(G_OBJECT(bubbleButton), "clicked",G_CALLBACK(bubble_pressed),NULL);
    g_signal_connect(G_OBJECT(armstrongButton), "clicked",G_CALLBACK(armstrong_pressed),NULL);
    g_signal_connect(G_OBJECT(fibButton), "clicked",G_CALLBACK(fib_pressed),NULL);
    g_signal_connect(G_OBJECT(terminalButton), "clicked",G_CALLBACK(terminal_pressed),NULL);

  
	g_object_unref(builder);
	gtk_widget_show(GTK_Window);

  	pthread_t id;
  	pthread_create(&id,NULL,update_time,NULL);
	gtk_main();

	return EXIT_SUCCESS;
}
