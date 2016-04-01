#define ROOMS "/players/slider/rooms/"
#define MONSTERS "/players/slider/monsters/"
#define OBJ "/players/slider/obj/"
#define TEXT "/players/slider/text/"
#define LOGS "/players/slider/logs/"
#define ETC "/players/slider/etc/"
 
#define PLAYER_NAME capitalize(this_player()->query_real_name())
#define PLAYER this_player()
#define PLAYER_ENV environment(this_player())
 
#define GETNAME query_real_name();
 
#define THIS_ENV environment(this_object())
#define THIS this_object()
