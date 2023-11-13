//
// Created by bruhpc on 10/27/23.
//

#ifndef SML_LIB_TERMINAL_COLORS_H
#define SML_LIB_TERMINAL_COLORS_H

#ifdef REMOVE_PREFIX

// Regular text
#define COLOR_BLK "\e[0;30m"
#define COLOR_RED "\e[0;31m"
#define COLOR_GRN "\e[0;32m"
#define COLOR_YEL "\e[0;33m"
#define COLOR_BLU "\e[0;34m"
#define COLOR_MAG "\e[0;35m"
#define COLOR_CYN "\e[0;36m"
#define COLOR_WHT "\e[0;37m"

//Regular bold text
#define COLOR_BBLK "\e[1;30m"
#define COLOR_BRED "\e[1;31m"
#define COLOR_BGRN "\e[1;32m"
#define COLOR_BYEL "\e[1;33m"
#define COLOR_BBLU "\e[1;34m"
#define COLOR_BMAG "\e[1;35m"
#define COLOR_BCYN "\e[1;36m"
#define COLOR_BWHT "\e[1;37m"

//Regular underline text
#define COLOR_UBLK "\e[4;30m"
#define COLOR_URED "\e[4;31m"
#define COLOR_UGRN "\e[4;32m"
#define COLOR_UYEL "\e[4;33m"
#define COLOR_UBLU "\e[4;34m"
#define COLOR_UMAG "\e[4;35m"
#define COLOR_UCYN "\e[4;36m"
#define COLOR_UWHT "\e[4;37m"

//Regular background
#define COLOR_BLKB "\e[40m"
#define COLOR_REDB "\e[41m"
#define COLOR_GRNB "\e[42m"
#define COLOR_YELB "\e[43m"
#define COLOR_BLUB "\e[44m"
#define COLOR_MAGB "\e[45m"
#define COLOR_CYNB "\e[46m"
#define COLOR_WHTB "\e[47m"

//High intensty background
#define COLOR_BLKHB "\e[0;100m"
#define COLOR_REDHB "\e[0;101m"
#define COLOR_GRNHB "\e[0;102m"
#define COLOR_YELHB "\e[0;103m"
#define COLOR_BLUHB "\e[0;104m"
#define COLOR_MAGHB "\e[0;105m"
#define COLOR_CYNHB "\e[0;106m"
#define COLOR_WHTHB "\e[0;107m"

//High intensty text
#define COLOR_HBLK "\e[0;90m"
#define COLOR_HRED "\e[0;91m"
#define COLOR_HGRN "\e[0;92m"
#define COLOR_HYEL "\e[0;93m"
#define COLOR_HBLU "\e[0;94m"
#define COLOR_HMAG "\e[0;95m"
#define COLOR_HCYN "\e[0;96m"
#define COLOR_HWHT "\e[0;97m"

//Bold high-intensity text
#define COLOR_BHBLK "\e[1;90m"
#define COLOR_BHRED "\e[1;91m"
#define COLOR_BHGRN "\e[1;92m"
#define COLOR_BHYEL "\e[1;93m"
#define COLOR_BHBLU "\e[1;94m"
#define COLOR_BHMAG "\e[1;95m"
#define COLOR_BHCYN "\e[1;96m"
#define COLOR_BHWHT "\e[1;97m"

//Reset
#define color_reset "\e[0m"
#define color_CRESET "\e[0m"
#define color_COLOR_RESET "\e[0m"
#endif

// Regular text
#define SML_COLOR_BLK "\e[0;30m"
#define SML_COLOR_RED "\e[0;31m"
#define SML_COLOR_GRN "\e[0;32m"
#define SML_COLOR_YEL "\e[0;33m"
#define SML_COLOR_BLU "\e[0;34m"
#define SML_COLOR_MAG "\e[0;35m"
#define SML_COLOR_CYN "\e[0;36m"
#define SML_COLOR_WHT "\e[0;37m"

//Regular bold text
#define SML_COLOR_BBLK "\e[1;30m"
#define SML_COLOR_BRED "\e[1;31m"
#define SML_COLOR_BGRN "\e[1;32m"
#define SML_COLOR_BYEL "\e[1;33m"
#define SML_COLOR_BBLU "\e[1;34m"
#define SML_COLOR_BMAG "\e[1;35m"
#define SML_COLOR_BCYN "\e[1;36m"
#define SML_COLOR_BWHT "\e[1;37m"

//Regular underline text
#define SML_COLOR_UBLK "\e[4;30m"
#define SML_COLOR_URED "\e[4;31m"
#define SML_COLOR_UGRN "\e[4;32m"
#define SML_COLOR_UYEL "\e[4;33m"
#define SML_COLOR_UBLU "\e[4;34m"
#define SML_COLOR_UMAG "\e[4;35m"
#define SML_COLOR_UCYN "\e[4;36m"
#define SML_COLOR_UWHT "\e[4;37m"

//Regular background
#define SML_COLOR_BLKB "\e[40m"
#define SML_COLOR_REDB "\e[41m"
#define SML_COLOR_GRNB "\e[42m"
#define SML_COLOR_YELB "\e[43m"
#define SML_COLOR_BLUB "\e[44m"
#define SML_COLOR_MAGB "\e[45m"
#define SML_COLOR_CYNB "\e[46m"
#define SML_COLOR_WHTB "\e[47m"

//High intensty background
#define SML_COLOR_BLKHB "\e[0;100m"
#define SML_COLOR_REDHB "\e[0;101m"
#define SML_COLOR_GRNHB "\e[0;102m"
#define SML_COLOR_YELHB "\e[0;103m"
#define SML_COLOR_BLUHB "\e[0;104m"
#define SML_COLOR_MAGHB "\e[0;105m"
#define SML_COLOR_CYNHB "\e[0;106m"
#define SML_COLOR_WHTHB "\e[0;107m"

//High intensty text
#define SML_COLOR_HBLK "\e[0;90m"
#define SML_COLOR_HRED "\e[0;91m"
#define SML_COLOR_HGRN "\e[0;92m"
#define SML_COLOR_HYEL "\e[0;93m"
#define SML_COLOR_HBLU "\e[0;94m"
#define SML_COLOR_HMAG "\e[0;95m"
#define SML_COLOR_HCYN "\e[0;96m"
#define SML_COLOR_HWHT "\e[0;97m"

//Bold high-intensity text
#define SML_COLOR_BHBLK "\e[1;90m"
#define SML_COLOR_BHRED "\e[1;91m"
#define SML_COLOR_BHGRN "\e[1;92m"
#define SML_COLOR_BHYEL "\e[1;93m"
#define SML_COLOR_BHBLU "\e[1;94m"
#define SML_COLOR_BHMAG "\e[1;95m"
#define SML_COLOR_BHCYN "\e[1;96m"
#define SML_COLOR_BHWHT "\e[1;97m"

//Reset
#define sml_color_reset "\e[0m"
#define sml_color_CRESET "\e[0m"
#define sml_color_COLOR_RESET "\e[0m"

#endif //SML_LIB_TERMINAL_COLORS_H
