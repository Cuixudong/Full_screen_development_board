#ifndef	__PY_MB_h__
#define	__PY_MB_h__
#include "pyinput.h"
//////////////////////////////////////////////////////////////////////////////////	 
//±¾³ÌĞò²Î¿¼×ÔÍøÂç²¢¼ÓÒÔĞŞ¸Ä
//ALIENTEK STM32¿ª·¢°å
//Æ´ÒôÊäÈë·¨ Çı¶¯´úÂë	   
//ÕıµãÔ­×Ó@ALIENTEK
//¼¼ÊõÂÛÌ³:www.openedv.com
//ĞŞ¸ÄÈÕÆÚ:2012/9/22
//°æ±¾£ºV1.0			    
//¹ãÖİÊĞĞÇÒíµç×Ó¿Æ¼¼ÓĞÏŞ¹«Ë¾  	 												    								  
//////////////////////////////////////////////////////////////////////////////////

//ºº×ÖÅÅÁĞ±í
const uint8_t PY_mb_space []={""};
const uint8_t PY_mb_a     []={"°¡°¢ëçß¹ï¹…àÄåHºÇëç"};
const uint8_t PY_mb_ai    []={"°®°£°¤°¥°¦°§°¨°©°ª°«°¬°­°¯ŞßàÈàÉæÈè¨êÓíÁïÍö°"};
const uint8_t PY_mb_an    []={"°²°³°´°µ°¶°¸°°°±ÚÏ°·ÛûŞîáíâÖèñï§ğÆ÷ö"};
const uint8_t PY_mb_ang   []={"°º°»°¹óa"};
const uint8_t PY_mb_ao    []={"°¼°½°¾°¿°À°Á°Â°Ã°ÄÛêŞÖà»òüöË÷¡÷éá®âÚåÛæÁæñéáñú"};
const uint8_t PY_mb_ba    []={"°Ë°Í°Ö°Î°Å°Æ°Ç°È°É°Ê°Ì°Ï°Ğ°Ñ°Ò°Ó°Ô°ÕÜØİÃá±å±îÙôÎöÑ÷É"};
const uint8_t PY_mb_bai   []={"°×°Ø°Ù°Ú°Û°Ü°İ°Ş²®Şãêş"};
const uint8_t PY_mb_ban   []={"°ë°ì°ß°à°á°â°ã°ä°å°æ°ç°è°é°ê°íÚæÛàêÚîÓñ£ñ­ô²"};
const uint8_t PY_mb_bang  []={"°î°ï°ğ°ñ°ò°ó°ô°õ°ö°÷°ø°ùİòäº"};
const uint8_t PY_mb_bao   []={"°ü±¦±£±§±¨±©°ú°û°ı°ş±¡±¢±¤±¥±ª±«±¬ÅÙÅÚÙèİáæßìÒğ±ñÙõÀöµ"};
const uint8_t PY_mb_bei   []={"±³±´±±±¶±­±®±¯±°±²±µ±·±¸±¹±º±»±ÛØÃÚéÚıÛıİÉİíßÂã£íÕğÇñØöÍ÷¹"};;
const uint8_t PY_mb_ben   []={"±¾±¿±¼±½ÛÎÛĞêÚï¼"};
const uint8_t PY_mb_beng  []={"°ö±À±Á±Â±Ã±Ä±ÅÜ¡àÔê´"};
const uint8_t PY_mb_bi    []={"±Æ±Ç±È±É±Ê±Ë±Ì±Í±Î±Ï±Ğ±Ñ±Ò±Ó±Ô±ÕØ°±Ö±×±Ø±Ù±Ú±Û±Ü±İÃØÃÚÙÂÛıÜÅÜêİ©İÉŞµßÁßÙáùâØã¹ääå¨åöåşæ¾æÔèµêÚî¯îéïõñÔóÙóëó÷ô°ôÅõÏ÷Â"};
const uint8_t PY_mb_bian  []={"±ß±à±á±ã±ä±å±Ş±â±æ±ç±è±éØÒÛÍÜĞâíãêçÂìÔí¾íÜñ¹ñÛòùóÖöı"};
const uint8_t PY_mb_biao  []={"±í±ê±ë±ìæ»æôè¼ì©ì­ì®ïÚïğñ¦ñÑ÷§÷Ô"};
const uint8_t PY_mb_bie   []={"±ğ±î±ï±ñõ¿"};
const uint8_t PY_mb_bin   []={"±ò±ó±ô±õ±ö±÷ÙÏáÙçÍçãéÄéëë÷ïÙ÷Æ÷Ş"};
const uint8_t PY_mb_bing  []={"±ø±ù±ú±û±ü±ı±ş²¡²¢ÆÁÙ÷ÙûÚûŞğéÄ"};
const uint8_t PY_mb_bo    []={"°Ø°Ù°ş±¡²©²£²¤²·²¥²¦²§²¨²ª²«²¬²­²®²¯²°²±²²²³²´²µØÃÙñŞ¬à£âÄéŞë¢íçîàğ¾ô¤õÀõËõÛ"};
const uint8_t PY_mb_bu    []={"²»²¼²½±¤²¶²·²¸²¹²º²¾²¿²ÀÆÒß²åÍê³êÎîĞîßõ³"};
const uint8_t PY_mb_ca    []={"²Áàêíå"};
const uint8_t PY_mb_cai   []={"²Å²Æ²Ç²Â²Ã²Ä²È²É²Ê²Ë²Ì"};
const uint8_t PY_mb_can   []={"²Í²Î²Ï²Ğ²Ñ²Ò²Óåîæîè²ôÓ÷õ"};
const uint8_t PY_mb_cang  []={"²Ô²Õ²Ö²×²ØØ÷"};
const uint8_t PY_mb_cao   []={"²İ²Ù²Ú²Û²ÜÜ³àĞäîó©ô½"};
const uint8_t PY_mb_ce    []={"²à²á²â²Ş²ßâü"};
const uint8_t PY_mb_cen   []={"²Îá¯ä¹"};
const uint8_t PY_mb_ceng  []={"²ã²äÔøàá"};
const uint8_t PY_mb_cha   []={"²å²æ²ç²è²é²ê²ë²ì²í²î²ïÉ²ÔûñÃàêâªâÇãâæ±è¾é«é¶éßïÊïï"};
const uint8_t PY_mb_chai  []={"²î²ğ²ñ²òÙ­îÎğûò²ö·"};
const uint8_t PY_mb_chan  []={"²ú²û²ü²ó²ô²õ²ö²÷²ø²ùåîµ¥ÙæÚÆİÛâÜâãäıå¤åñæ¿êèìøïâó¸õğ"};
const uint8_t PY_mb_chang []={"³¤³§²ı²ş³¡³¢³£³¥³¦³¨³©³ª³«ØöÛËÜÉİÅáäâêã®ãÑæ½æÏêÆë©öğ"};
const uint8_t PY_mb_chao  []={"³¬³­³®³¯³°³±³²³³³´´Â½Ëâ÷êËñé"};
const uint8_t PY_mb_che   []={"³µ³¶³·³¸³¹³ºÛååøíº"};
const uint8_t PY_mb_chen  []={"³»³¼³½³¾³¿³À³Á³Â³Ã³Ä³ÆÚÈÚßŞÓàÁå·è¡é´í×ö³"};
const uint8_t PY_mb_cheng []={"³Å³Æ³Ç³È³É³Ê³Ë³Ì³Í³Î³Ï³Ğ³Ñ³Ò³ÓÊ¢Ø©ÛôàááçèÇèßëóîªîñîõñÎòÉõ¨"};
const uint8_t PY_mb_chi   []={"³Ô³Õ³Ö³×³Ø³Ù³Ú³Û³Ü³İ³Ş³ß³à³á³â³ãó×ß³ßêÙÑÛæÜ¯Üİà´àÍáÜâÁæÊë·í÷ğ·ñ¡ñİò¿ó¤óøôùõØ÷Î"};
const uint8_t PY_mb_chong []={"³ä³å³æ³ç³èÖÖÖØÜûâçã¿ï¥ô©ô¾öÅ"};
const uint8_t PY_mb_chou  []={"³é³ê³ó³ë³ì³í³î³ï³ğ³ñ³ò³ôÙ±àüã°ñ¬öÅ"};
const uint8_t PY_mb_chu   []={"³ö³õ³÷³ø³ù³ú³û³ü³ı³ş´¡´¢´£´¤´¥´¦ĞóØ¡Û»âğãÀç©èÆèúéËñÒòÜõé÷í"};
const uint8_t PY_mb_chuai []={"´§ŞõàÜëúõß"};
const uint8_t PY_mb_chuan []={"´¨´©´ª´«´¬´­´®â¶å×çİë°îËô­"};
const uint8_t PY_mb_chuang[]={"´¯´°´±´²´³´´âëğÚ"};
const uint8_t PY_mb_chui  []={"´µ´¶´·´¸´¹Úïé¢é³"};
const uint8_t PY_mb_chun  []={"´º´»´¼´½´¾´¿´Àİ»ğÈòí"};
const uint8_t PY_mb_chuo  []={"´Á´Âà¨åÁê¡õÖöº"};
const uint8_t PY_mb_ci    []={"´Ë´Ì´Í´ÎËÅ²î´Ã´Ä´Å´Æ´Ç´È´É´Ê×ÈÜëßÚìôğËôÒôÙ"};
const uint8_t PY_mb_cong  []={"´Ó´Ô´Ï´Ğ´Ñ´ÒÜÊäÈæõçıè®èÈ"};
const uint8_t PY_mb_cou   []={"´Õé¨ê£ëí"};
const uint8_t PY_mb_cu    []={"´Ö´×´Ø´ÙİıáŞâ§éãõ¡õ¾õí"};
const uint8_t PY_mb_cuan  []={"´Ú´Û´ÜÔÜÙàß¥ìàïé"};
const uint8_t PY_mb_cui   []={"´İ´Ş´ß´à´á´â´ã´äİÍßıã²è­éÁë¥ö¿"};
const uint8_t PY_mb_cun   []={"´å´æ´çââñå"};
const uint8_t PY_mb_cuo   []={"´è´é´ê´ë´ì´íØÈáÏëâï±ïóğîğûõºõãõò"};
const uint8_t PY_mb_da    []={"´ó´î´ï´ğ´ñ´òŞÇßÕàªâòæ§í³ğãñ×óÎ÷°÷²"};
const uint8_t PY_mb_dai   []={"´ó´ô´õ´ö´÷´ø´ù´ú´û´ü´ı´şµ¡÷ìÜ¤ß°ß¾á·åÊææçªçé"};
const uint8_t PY_mb_dan   []={"µ¢µ£µ¤µ¥µ¦µ§µ¨µ©µªµ«µ¬µ­µ®µ¯µ°ÉÄÊ¯ÙÙİÌà¢å£ééêæíñğãğ÷ñõóì"};
const uint8_t PY_mb_dang  []={"µ±µ²µ³µ´µµÚÔÛÊİĞå´í¸îõñÉ"};
const uint8_t PY_mb_dao   []={"µ¶µ·µ¸µ¹µºµ»µ¼µ½µ¾µ¿µÀµÁØÖß¶àüâáë®ìâôî"};
const uint8_t PY_mb_de    []={"µÂµÃµÄµØï½"};
const uint8_t PY_mb_dei   []={"µÃ"};
const uint8_t PY_mb_deng  []={"³ÎµÅµÆµÇµÈµÉµÊµËàâáØê­íãïëô£"};
const uint8_t PY_mb_di    []={"µÄµÖµ×µØµÙµÚµÛµÜµİµÌµÍµÎµÏµĞµÑµÒµÓµÔµÕµŞÌáØµÙáÚ®ÚĞÛ¡Ûæİ¶àÖæ·èÜé¦êëíÆíÚíûïáôÆ÷¾"};
const uint8_t PY_mb_dia   []={"àÇ"};
const uint8_t PY_mb_dian  []={"µçµêµëµãµäµåµìµíµîµßµàµáµâµæµèµéÚçÛãáÛçèîäñ°ñ²ô¡õÚ"};
const uint8_t PY_mb_diao  []={"µõµóµôµöµ÷µïµğµñµòîöï¢õõöô"};
const uint8_t PY_mb_die   []={"µøµùµúµûµüµıµşÛìÜ¦Şéà©ëºğ¬ñóõŞöø"};
const uint8_t PY_mb_ding  []={"¶¡¶¢¶£¶¤¶¥¶¦¶§¶¨¶©Øêà¤çàëëíÖî®îúğÛñôôú"};
const uint8_t PY_mb_diu   []={"¶ªîû"};
const uint8_t PY_mb_dong  []={"¶«¶¬¶­¶®¶¯¶°¶±¶²¶³¶´ßËá´á¼ë±ëËëØíÏğ´"};
const uint8_t PY_mb_dou   []={"¶¹¶º¶»¶¼¶µ¶¶¶·¶¸İúñ¼ò½óû"};
const uint8_t PY_mb_du    []={"¶Ç¶È¶É¶¼¶½¶¾¶¿¶À¶Á¶Â¶Ã¶Ä¶Å¶Æ¶ÊÜ¶à½äÂèüë¹ó¼óÆ÷Ç÷ò"};
const uint8_t PY_mb_duan  []={"¶Ë¶Ì¶Í¶Î¶Ï¶Ğé²ìÑóı"};
const uint8_t PY_mb_dui   []={"¶Ñ¶Ò¶Ó¶Ôí¡í­íÔ"};
const uint8_t PY_mb_dun   []={"¶Ü¶Õ¶Ö¶×¶Ø¶Ù¶Ú¶Û¶İãçìÀí»íâíïïæõ»"};
const uint8_t PY_mb_duo   []={"¶à¶ä¶È¶Ş¶ß¶á¶â¶ã¶å¶æ¶ç¶è¶éÍÔßÍßáãõç¶îìñÖõâ"};
const uint8_t PY_mb_e     []={"°¢¶ê¶ë¶ì¶í¶î¶ï¶ğ¶ñ¶ò¶ó¶ô¶õ¶öÅ¶Ø¬ÚÌÛÑÜÃİ­İàßÀãµåíæ¹éîëñï°ïÉğÊò¦öù"};
const uint8_t PY_mb_ei    []={"ÚÀ"};
const uint8_t PY_mb_en    []={"¶÷İìŞô"};
const uint8_t PY_mb_er    []={"¶ş¶ø¶ù¶ú¶û¶ü¶ı·¡åÇçíîïğ¹öÜ"};
const uint8_t PY_mb_fa    []={"·¢·£·¤·¥·¦·§·¨·©ÛÒíÀ"};
const uint8_t PY_mb_fan   []={"·²·³·´·µ·¶···¸·¹·º·ª·«·¬·­·®·¯·°·±Ş¬ŞÀá¦èóìÜî²õì"};
const uint8_t PY_mb_fang  []={"·»·¼·½·¾·¿·À·Á·Â·Ã·Ä·ÅØÎÚúèÊîÕô³öĞ"};
const uint8_t PY_mb_fei   []={"·Æ·Ç·È·É·Ê·Ë·Ì·Í·Î·Ï·Ğ·ÑÜÀáôì³ã­åúç³äÇé¼êÚëèìéíÉïĞğòòãóõôäö­öî"};
const uint8_t PY_mb_fen   []={"·Ö·Ò·Ü·İ·Ş·ß·à·Ó·Ô·Õ·×·Ø·Ù·Ú·ÛÙÇå¯çãèûêÚö÷÷÷"};
const uint8_t PY_mb_feng  []={"·á·â·ã·ä·å·æ·ç·ï·è·é·ê·ë·ì·í·îÙºÛºİ×ßôããí¿"};
const uint8_t PY_mb_fo    []={"·ğ"};
const uint8_t PY_mb_fou   []={"·ñó¾"};
const uint8_t PY_mb_fu    []={"¸´·ğ¸µ¸¶¸·¸¸·ò·ó·ô·õ¸¾·ö·÷·ø·ù·ú·û·ü·ı·ş¸¡¸¢¸£¸¤¸¥¸¦¸§¸¨¸©¸ª¸«¸¬¸­¸®¸¯¸°¸±¸²¸³¸¹¸º¸»¸¼¸½¸¿¸ÀÙëÙìÚâÛ®Ü½ÜÀÜŞÜòİ³İÊŞÔß»á¥âöäæåõæÚæâç¦ç¨èõêçìğíÉíêíëî·ïûğ¥ò¶òİòğòóôïõÃõÆöÖöû"};
const uint8_t PY_mb_ga    []={"¸Á¸Â¼Ğ¿§Ù¤ŞÎæØæÙê¸îÅ"};
const uint8_t PY_mb_gai   []={"¸Ã¸Ä¸Å¸Æ¸Ç¸È½æØ¤ÚëÛòê®êàëÜ"};
const uint8_t PY_mb_gan   []={"¸É¸Ê¸Ë¸Ì¸Í¸Î¸Ï¸Ğ¸Ñ¸Ò¸ÓÛáÜÕŞÏß¦ãïäÆä÷ç¤éÏêºí·ğáôû"};
const uint8_t PY_mb_gang  []={"¸Ô¸Õ¸Ö¸×¸Ø¸Ù¸Ú¸Û¸Ü¿¸í°î¸óà"};
const uint8_t PY_mb_gao   []={"¸æ¸Ş¸ß¸à¸İ¸á¸â¸ã¸ä¸åØºÚ¾Û¬Ş»çÉéÀéÂê½ï¯"};
const uint8_t PY_mb_ge    []={"¸ö¸÷¸Ç¸ç÷Àëõ¸è¸é¸ê¸ë¸ì¸í¸î¸ï¸ğ¸ñ¸ò¸ó¸ô¸õºÏ¿©ØªØîÛÁÛÙÜªàÃæüë¡îşïÓñËò´ô´"};
const uint8_t PY_mb_gei   []={"¸ø"};
const uint8_t PY_mb_gen   []={"¸ù¸úØ¨İ¢ßçôŞ"};
const uint8_t PY_mb_geng  []={"¸û¸ü¸ı¸ş¹¡¹¢¹£¾±ßìâÙç®öá"};
const uint8_t PY_mb_gong  []={"¹¤¹²¹¥¹¦¹§¹«¹¬¹­¹¨¹©¹ª¹®¹¯¹°¹±ò¼ŞÃçîëÅö¡"};
const uint8_t PY_mb_gou   []={"¹³¹´¹µ¹¶¹»¹¸¹¹¹ºØşÚ¸¹·óôá¸åÜæÅçÃèÛêíì°óÑ÷¸"};
const uint8_t PY_mb_gu    []={"¹Ã¹À¹Á¹Â¹½¹¾¹¼¹¿¹Ä¹Å¹Æ¹Ç¹È¹É¹Ê¹Ë¹Ì¹Í¼ÖØÅÚ¬İÔáÄãéèôéïêôêöëûì±î­î¹îÜïÀğ³ğÀğóòÁôşõıöñ÷½"};
const uint8_t PY_mb_gua   []={"¹Î¹Ï¹Ğ¹Ñ¹Ò¹ÓØÔÚ´ßÉèéëÒğ»"};
const uint8_t PY_mb_guai  []={"¹Ô¹Õ¹ÖŞâ"};
const uint8_t PY_mb_guan  []={"¹Ø¹Ù¹Ú¹Û¹Ü¹İ¹Ş¹ß¹à¹áÂÚÙÄİ¸¹×ŞèäÊîÂğÙ÷¤"};
const uint8_t PY_mb_guang []={"¹â¹ã¹äßÛáîèæë×"};
const uint8_t PY_mb_gui   []={"¹å¹æ¹ç¹è¹é¹ê¹ë¹ì¹í¹î¹ğ¹ñ¹ò¹ó¹ô¹ïÈ²ØĞØÛâÑå³æ£èíêÁêĞğ§óşöÙ÷¬"};
const uint8_t PY_mb_gun   []={"¹õ¹ö¹÷ÙòçµíŞöç"};
const uint8_t PY_mb_guo   []={"¹ø¹ù¹ú¹û¹ü¹ıÎĞÙåÛöŞâßÃàşáÆâ£é¤ë½ï¾ñøòäòå"};
const uint8_t PY_mb_ha    []={"¹ş¸òîş"};
const uint8_t PY_mb_hai   []={"»¹¿Èº¢º£º¦º¤º¥º§º¡àËëÜõ°"};
const uint8_t PY_mb_han   []={"º¹ººº°º®º¬º­º¯º±º¨ºµº¶º·º¸º©ºªº«º²º³÷ıº´ÚõİÕŞşå«êÏìÊñüò¥òÀ"};
const uint8_t PY_mb_hang  []={"ĞĞº»º¼º½¿ÔÏïãìç¬ñş"};
const uint8_t PY_mb_hao   []={"ºÂºÃºÄºÅê»ğ©ºÁºÆå°¸äº¾º¿ºÀºÑİïŞ¶àÆàãå©ò«òº"};
const uint8_t PY_mb_he    []={"ºÇºÈºÉºÊºËºÌºÍºÎºÏºÓºĞºÑºÒºÔºÕºØºÖº×ÏÅÚ­ÛÀÛÖàÀãØæüêÂîÁò¢òÂôç"};
const uint8_t PY_mb_hei   []={"ºÚºÙ"};
const uint8_t PY_mb_hen   []={"ºÛºÜºİºŞ"};
const uint8_t PY_mb_heng  []={"ºßºàºáºâºãŞ¿çñèì"};
const uint8_t PY_mb_hong  []={"ºìºäºåºæºçºèºéºêºëÙäÙêÚ§İ¦Ş®Ş°ãÈãü"};
const uint8_t PY_mb_hou   []={"ºóºíºîºïºğºñºòÜ©ááåËğúóóô×ö×÷¿"};
const uint8_t PY_mb_hu    []={"»¤»¥»¦»§ºËºôºõºöº÷ºøºùºúºû»¢ºüºıºş»¡»£Ùüßüàñá²â©âïã±ä°äïçúéÎéõì²ìÃìÎìæìèìïğ­ğÀğÉğ×ò®óËõ­õú÷½"};
const uint8_t PY_mb_hua   []={"»¨»ª»«»¬»©»­»®»¯»°æèèëí¹îü"};
const uint8_t PY_mb_huai  []={"»µ»±»²»³»´õ×"};
const uint8_t PY_mb_huan  []={"»¶»·»¸»¹»º»»»¼»½»¾»À»Á»Â»Ã÷ßä½»¿Û¨Û¼ÛùİÈß§à÷âµä¡äñå¾åÕçÙïÌöé"};
const uint8_t PY_mb_huang []={"»Î»Ä»Å»Æ»Ç»È»É»Ê»Ë»Ì»Í»Ï»Ğ»ÑÚòáåäÒäêåØè«ëÁñ¥ó¨óòöü"};
const uint8_t PY_mb_hui   []={"»á»Ø»Ù»Ú»Ò»Ó»Ô»Õ»Ö»×»Û»Ü»İ»Ş»ß»à»â»ã»ä»å»æåçÀ£Ú¶ÜîÜöŞ¥ßÔßÜà¹ãÄä§ä«çÀèíêÍí£ò³ó³÷â"};
const uint8_t PY_mb_hun   []={"»ç»è»é»ê»ë»ìÚ»âÆãÔäãçõ"};
const uint8_t PY_mb_huo   []={"ºÍ»í»î»ï»ğ»ñ»ò»ó»ô»õ»öØåŞ½ß«àëâ·îØïÁïìñëó¶"};
const uint8_t PY_mb_ji    []={"¼Æ¼Ç¸ø¼¼»÷»ù¼¸¼¹¼º»ø¼®¼¯¼°¼±¼²¼³¼´¼µ¼¶¼·¼»¼È¼É¼Ê¼½¼¾¼¿¼À¼Á»ú»û»ü»ı¼¡¼¢¼£¼¤¼¥¼¦¼§¼¨¼©¼ª¼«¼¬»ş¼­¼Â¼Ã¼Ä¼Å¼Ë¼Ì¼Í½åÆæÏµØ¢Ø½ØÀØŞÙ¥ÙÊÛÔÜ¸ÜÁÜùİ½İğŞªŞáß´ßÒßâßóá§áÕä©åæåìæ÷çÜçáé®éêêªê«êåêéê÷ì´í¶î¿ïúğ¢ñ¤ò±óÅóÇôßõÒõÕö«öİöê÷Ù÷ä"};
const uint8_t PY_mb_jia   []={"¼Ò¼Ó¼Î¼Ğ¼Ñ¼Ô¼Õ¼Ö¼×¼Ø¼Ù¼Ú¼Û¼Ü¼İ¼Ş¼ÏÇÑØÅÙ¤Û£İçáµä¤åÈçìê©ëÎí¢îòîşïØğèğıñÊòÌóÕôÂõÊ"};
const uint8_t PY_mb_jian  []={"½¨¼û¼ş¼ò½¡¼õ¼ß¼ö¼à¼ñ¼ó¼ô¼á¼â¼ä¼å¼æ¼ç¼è¼é¼ê¼ë¼ì¼í¼î¼ï¼ğ¼ã¼÷¼ø¼ù¼ú¼ü¼ı½¢½£½¤½¥½¦½§ÙÔÚÉÚÙÚÚİÑİóŞöàîäÕå¿åÀçÌèÅé¥ê§ê¯êğêùë¦ëìíúïµğÏñĞóÈôåõÂõİöä÷µ"};
const uint8_t PY_mb_jiang []={"½²ºç½©½ª½«½¬½­½®½¯½°½±½³½´½µÇ¿Üüä®ç­çÖêñíäñğôİôø"};
const uint8_t PY_mb_jiao  []={"½Ğ½Ï¾õ½ÇĞ£½¶½·½¸½¹½º½»½¼½½½¾½¿½À½Á½Â½Ã½Ä½Å½Æ½È½É½Ê½Ë½Ì½Í½Î½ÑÙ®ÙÕÜ´ÜúŞØàİá½áèæ¯ë¸ğ¨ğÔòÔõ´õÓöŞ"};
const uint8_t PY_mb_jie   []={"½à½á½â½ã½ä½Ò½Ü½Ó½Ô½ç½è½é½İ½Ş½Õ½Ö½×½Ø½Ù½Ú½Û½ß½å½æ½ê½ë½ìÙÊÚ¦ÚµÚàŞ×à®àµæ¼æİèîíÙïÇğÜò¡ò»ôÉöÚ÷º"};
const uint8_t PY_mb_jin   []={"½í¾¡½î½ï½ğ½ñ½ò½ô½õ½ö½÷½ø½ù½ú½û½ü½ı½ş¾¢½óÚáİ£İÀàäâËâÛæ¡çÆèªéÈêáêîîÄñÆñæ"};
const uint8_t PY_mb_jing  []={"¾©¾ª¾«¾­¾®¾¦¾§¾°¾»¾±¾²¾³¾´¾¯¾µ¾¶¾¹¾º¾¢¾£¾¤¾¥¾¨¾¬¾·¾¸ØÙÙÓÚåÚêİ¼â°ã½ãşåÉåòæºëÂëÖëæìºö¦"};
const uint8_t PY_mb_jiong []={"¾¼¾½ØçåÄìç"};
const uint8_t PY_mb_jiu   []={"¾Å¾Í¾È¾¾¾¿¾À¾Á¾Â¾Ã¾Ä¾Æ¾É¾Ê¾Ë¾Ì¾Î¾ÇÙÖà±ãÎèÑèêğ¯ğÕôñ÷İ"};
const uint8_t PY_mb_ju    []={"¾Ş¾ß¾à¾ã¾ä¾å³µ¹ñ¾ç¾Ó¾Ô¾Õ¾Ö¾×¾Ø¾Ù¾Ú¾Û¾Ü¾İ¾á¾â¾æ¾Ï¾Ğ¾Ñ¾ÒÙÆÚªÜÄÜÚÜìŞäåáåğè¢èÛé§é°é·éÙêøì«îÒï¸ñÀñÕôòõ¶õáö´öÂöÄ÷¶"};
const uint8_t PY_mb_juan  []={"¾ì¾í¾è¾é¾ê¾ë¾îÈ¦Û²áúä¸èğîÃïÃïÔöÁ"};
const uint8_t PY_mb_jue   []={"¾ö¾÷¾ø¾õ½Ç¾ò¾ó½À½Å¾ï¾ğ¾ñ¾ôØÊØãÚÜÛÇÜ¥Ş§àÙáÈâ±æŞçåèöéÓìßïãõêõû"};
const uint8_t PY_mb_jun   []={"¾ü¾ı¾ù¾ú¾û¾ş¿¡¿¢¿£¿¤¿¥¹êŞÜñäóŞ÷å"};
const uint8_t PY_mb_ka    []={"¿¨¿¦¿§¿©ØûßÇëÌ"};
const uint8_t PY_mb_kai   []={"¿ª¿«¿¬¿­¿®ØÜÛîİÜâéâıîøï´ïÇ"};
const uint8_t PY_mb_kan   []={"¿´¿¯¿°¿±¿²¿³Ù©íèî«ÛÉİ¨ãÛ¼÷ê¬"};
const uint8_t PY_mb_kang  []={"¿µ¿¶¿·¿¸¿¹¿º¿»ØøãÊîÖ"};
const uint8_t PY_mb_kao   []={"¿¼¿¿¿½¿¾èàêûîíåê"};
const uint8_t PY_mb_ke    []={"¿É¿Ê¿Ë¿Æ¿Ì¿Í¿Îà¾¿À¿Á¿Â¿Ã¿Ä¿Å¿Ç¿Èã¡òòá³äÛïıæìç¼çæéğë´î§îİîşºÇï¾ğâñ½ò¤òÂ÷Á"};
const uint8_t PY_mb_ken   []={"¿Ï¿Ğ¿Ñ¿ÒñÌ"};
const uint8_t PY_mb_keng  []={"¿Ó¿Ôï¬ëÖîï"};
const uint8_t PY_mb_kong  []={"¿Õ¿Ö¿×¿ØÙÅáÇóí"};
const uint8_t PY_mb_kou   []={"¿Ù¿Ú¿Û¿ÜÜÒŞ¢ßµíîóØ"};
const uint8_t PY_mb_ku    []={"¿İ¿Ş¿ß¿à¿á¿â¿ãç«÷¼ØÚÜ¥à·"};
const uint8_t PY_mb_kua   []={"¿ä¿å¿æ¿ç¿èÙ¨ï¾"};
const uint8_t PY_mb_kuai  []={"»á¿é¿ê¿ë¿ìØáÛ¦ßàáöëÚ"};
const uint8_t PY_mb_kuan  []={"¿í¿î÷Å"};
const uint8_t PY_mb_kuang []={"¿ö¿ï¿ğ¿ñ¿ò¿ó¿ô¿õÚ²Ú¿Ú÷ÛÛŞÅßÑæşêÜ"};
const uint8_t PY_mb_kui   []={"¿÷¿ø¿ù¿ú¿û¿ü¿ı¿şÀ¡À¢À£Ø¸ØÑåÓî¥õÍÙçÚóİŞŞñà­à°ã¦ã´êÒñùòñóñ"};
const uint8_t PY_mb_kun   []={"À¤À¥À¦À§ã§çûï¿õ«öïãÍ÷Õ"};
const uint8_t PY_mb_kuo   []={"À¨À©ÀªÀ«òÒ"};
const uint8_t PY_mb_la    []={"À¬À­À®À¯À°À±À²ÂäØİååê¹íÇğø"};
const uint8_t PY_mb_lai   []={"À³À´ÀµáÁáâäµäşêãíùñ®ô¥ïª"};
const uint8_t PY_mb_lan   []={"À¶À·À¸À¹ÀºÀ»À¼À½À¾À¿ÀÀÀÁÀÂÀÃÀÄá°äíé­ìµïçñÜî½"};
const uint8_t PY_mb_lang  []={"ÀÉÀÊÀËÀÅÀÆÀÇÀÈà¥ãÏòëï¶İõïüİ¹"};
const uint8_t PY_mb_lao   []={"ÀÌÀÍÀÎÀÏÀĞÀÑÀÒÀÓÀÔÂäÂçßëáÀõ²èáîîï©ğìñì"};
const uint8_t PY_mb_le    []={"ÀÕÀÖÁËØìß·ãî÷¦"};
const uint8_t PY_mb_lei   []={"ÀÛÀÕÀ×ÀØÀÙÀÚÀÜÀİÀŞÀßÀàÀáÙúÚ³àÏæĞçĞéÛñçõª"};
const uint8_t PY_mb_leng  []={"ÀâÀãÀäÜ¨ã¶"};
const uint8_t PY_mb_li    []={"ÀûÁ¦ÀúÀ÷Á¢Á£ÀñÁ¤ÀôÀíÀîÀïÀåÀøÀöÀæÀçÁ¥ÀèÀéÀëÀìÀğÀõÀùÀòÀóÀêÀüÀıÀşÁ¡Á§Á¨ØªÙ³ÙµÛªÛŞÜÂİ°İñŞ¼ß¿à¦à¬áûäàå¢åÎæ²æËæêçÊèÀèİéöìåíÂíÇîºî¾ï®ğ¿ğİğßòÃòÛó»óÒóöôÏõ·õÈö¨öâ÷¯÷ó"};
const uint8_t PY_mb_lia   []={"Á©"};
const uint8_t PY_mb_lian  []={"ÁªÁ«Á¬Á®Á¯Á°Á±Á²Á³Á´ÁµÁ¶Á·äòÁ­å¥çöé¬ŞÆéçİüì¡ñÍñÏó¹öã"};
const uint8_t PY_mb_liang []={"Á½ÁÁÁ©Á¸Á¹ÁºÁ»Á¼Á¾Á¿ÁÀÁÂÜ®İ¹é£õÔ÷Ë"};
const uint8_t PY_mb_liao  []={"ÁËÁÃÁÏÁÄÁÅÁÆÁÇÁÈÁÉÁÊÁÌÁÍÁÎŞ¤ŞÍàÚâ²å¼çÔîÉğÓ"};
const uint8_t PY_mb_lie   []={"ÁĞÁÑÁÒÁÓä£ÁÔÙıÛøŞæßÖôóõñ÷à"};
const uint8_t PY_mb_lin   []={"ÁÙÁÚÁŞÁàÁÕÁÖÁ×ÁØÁÛÁÜÁİÁßİşßøá×âŞãÁåàéİê¥ì¢î¬ôÔõï÷ë"};
const uint8_t PY_mb_ling  []={"ÁîÁéÁíÀâÁáÁâÁãÁäÁåÁæÁçÁèÁêÁëñöÁìÛ¹ÜßßÊàòãöç±èÚèùê²òÈôáöì"};
const uint8_t PY_mb_liu   []={"ÁõÁùÁïÁğÁñÁòÁóÁôÁöÁ÷ÁøÂµÂ½ä¯åŞæòç¸ì¼ìÖï³ïÖğÒöÌ"};
const uint8_t PY_mb_lo    []={"¿©"}; 
const uint8_t PY_mb_long  []={"ÁúÅªÁûÁüÁıÁşÂ¡Â¢Â£Â¤ÛâÜ×ãñççèĞëÊíÃñª"};
const uint8_t PY_mb_lou   []={"Â¥Â¦Â§Â¨Â©ÂªÂ¶ÙÍİäà¶áĞïÎğüñïò÷÷Ã"};
const uint8_t PY_mb_lu    []={"ÁùÂ«Â¬Â­Â®Â¯Â°Â±Â²Â³Â´ÂµÂ¶Â·Â¸Â¹ÂºÂ»Â¼Â½Â¾ÂÌÛäß£ààãòäËäõåÖè´èÓéÖéñéûê¤êÚëªëÍïåğµğØóüôµöÔ"};
const uint8_t PY_mb_lv    []={"ÂËÂÊÂÌÂÀÂÁÂÂÂÃÂÄÂÅÂÆÂÇÂÈÂÉÂ¿ñÚÙÍŞÛãÌéµëöïù"}; 
const uint8_t PY_mb_luan  []={"ÂÒÂÏÂÍÂÎÂĞÂÑ"};
const uint8_t PY_mb_lue   []={"ÂÓÂÔï²"};
const uint8_t PY_mb_lun   []={"ÂØÂÕÂÖÂ×ÂÙÂÚÂÛàğ"};
const uint8_t PY_mb_luo   []={"ÂäÂŞ¸õ¿©ÀÓÂÜÂİÂßÂàÂáÂâÂãÂåÂæÂçÙÀÙùÜıŞÛŞûâ¤ãøäğçóé¡ëáíÑïİñ§öÃ"};
const uint8_t PY_mb_m     []={"ß¼"};  
const uint8_t PY_mb_ma    []={"ÂèÂéÂêÂëÂìÂíÂîÂïÂğÄ¦Ä¨ßéáïæÖè¿ó¡"};
const uint8_t PY_mb_mai   []={"ÂñÂ÷ÂøÂùÂúÂûÂüÂıÂşÃ¡Ü¬á£çÏì×ïÜò©òı÷©÷´"};
const uint8_t PY_mb_man   []={"ÂùÂøÂ÷ÂúÂüÃ¡ÂıÂşÂû"};
const uint8_t PY_mb_mang  []={"Ã¢Ã£Ã¤Ã¥Ã¦Ã§ÚøäİíËòş"};
const uint8_t PY_mb_mao   []={"Ã¨Ã©ÃªÃ«Ã¬÷ÖÃ®Ã¯Ã°Ã±Ã²Ã³ÙóÃ­Üâá¹ã÷è£êÄêóë£ì¸í®î¦òúó±"};
const uint8_t PY_mb_me    []={"Ã´"};
const uint8_t PY_mb_mei   []={"Ã¿ÃÃÃÀÃµÃ¶ÃÁÃÂñÇ÷ÈÃ·Ã¸Ã¹ÃºÃ»Ã¼Ã½Ã¾ÃÄİ®áÒâ­ä¼äØé¹ïÑğÌ"};
const uint8_t PY_mb_men   []={"ÃÅÃÆÃÇŞÑìËí¯îÍ"};
const uint8_t PY_mb_meng  []={"ÃÈÃÎÃÉÃÊÃËÃÌÃÍÃÏÛÂİùŞ«ãÂëüíæòµòìó·ô»ô¿"};
const uint8_t PY_mb_mi    []={"ÃĞÃÑÃÒÃÓÃÔÃÕÃÖÃ×ÃØÃÙÃÚÃÛÃÜ÷çÚ×ÃİØÂÚ¢ŞÂßäà×â¨ãèåµåôæùëßìòôÍôé÷ã"};
const uint8_t PY_mb_mian  []={"ÃæÃŞÃßÃàÃáÃâÃãÃäÃåãæäÅäÏå²ëïíí"};
const uint8_t PY_mb_miao  []={"ÃçÃèÃéÃêÃëÃìÃíÃîß÷åãç¿çÑèÂíµíğğÅ"};
const uint8_t PY_mb_mie   []={"ÃïÃğØ¿ßãóúóº"};
const uint8_t PY_mb_min   []={"ÃñÃòÃóÃôÃõÃöÜåáºãÉãıçÅçäçëíªö¼÷ª"};
const uint8_t PY_mb_ming  []={"Ã÷ÃøÃùÃúÃûÃüÚ¤ÜøäéêÔî¨õ¤"};
const uint8_t PY_mb_miu   []={"ÃıçÑ"};
const uint8_t PY_mb_mo    []={"ÂöÃ»ÃşÄ¡Ä¢Ä£Ä¤Ä¥Ä¦Ä§Ä¨Ä©ÄªÄ«Ä¬Ä­Ä®Ä¯Ä°÷áÍòÚÓÜÔİëâÉæÆéâïÒï÷ñ¢ñòõöõø"};
const uint8_t PY_mb_mou   []={"Ä±Ä²Ä³Ù°ßèçÑíøòÖöÊ"};
const uint8_t PY_mb_mu    []={"Ä¾Ä¿ÄÀÄ£Ä²Ä´ÄµÄ¶Ä·Ä¸Ä¹ÄºÄ»Ä¼Ä½ÄÁÄÂÜÙãåØïÛéë¤îâ"};
const uint8_t PY_mb_na    []={"ÄÃÄÄÄÅÄÆÄÇÄÈÄÉŞàëÇïÕñÄ"};
const uint8_t PY_mb_nai   []={"ÄÊÄËÄÌÄÍÄÎØ¾Ù¦ÜµİÁèÍ"};
const uint8_t PY_mb_nan   []={"ÄÏÄĞÄÑà«àïéªëîòïôö"};
const uint8_t PY_mb_nang  []={"ÄÒàìâÎß­êÙ"};
const uint8_t PY_mb_nao   []={"ÄÓÄÔÄÕÄÖÄ×Ø«ÛñßÎâ®è§íĞîóòÍ"};
const uint8_t PY_mb_ne    []={"ÄÄÄØÚ«"};
const uint8_t PY_mb_nei   []={"ÄÚÄÙ"};
const uint8_t PY_mb_nen   []={"ÄÛí¥"};
const uint8_t PY_mb_neng  []={"ÄÜ"};
const uint8_t PY_mb_ng    []={"àÅ"}; 
const uint8_t PY_mb_ni    []={"ÄãÄØÄâÄáÄİÄŞÄßÄàÄäÄåÄæÄçÙ£Ûèâ¥âõêÇì»ìòí«íşîêöò"};
const uint8_t PY_mb_nian  []={"ÄèÄéÄêÄëÄìÄíÄîØ¥Ûşéığ¤öÓöó"};
const uint8_t PY_mb_niang []={"ÄïÄğ"};
const uint8_t PY_mb_niao  []={"ÄñÄòëåôÁÜàæÕ"};
const uint8_t PY_mb_nie   []={"ÄóÄôÄõÄöÄ÷ÄøÄùõæŞÁà¿Ø¿Úíò¨ô«"};
const uint8_t PY_mb_nin   []={"Äú"};
const uint8_t PY_mb_ning  []={"ÄûÄüÄıÄşÅ¡Å¢ØúßÌå¸ñ÷"};
const uint8_t PY_mb_niu   []={"Å£Å¤Å¥Å¦ŞÖæ¤áğâî"};
const uint8_t PY_mb_nong  []={"Å§Å¨Å©ÅªÙ¯ßæ"};
const uint8_t PY_mb_nou   []={"ññ"};
const uint8_t PY_mb_nu    []={"Å«Å¬Å­åóæÀæÛæå"};
const uint8_t PY_mb_nuan  []={"Å¯"};
const uint8_t PY_mb_nue   []={"Å±Å°"};
const uint8_t PY_mb_nuo   []={"ÄÈÅ²Å³Å´ÅµÙĞŞùßöï»"};
const uint8_t PY_mb_nv    []={"Å®í¤îÏô¬"};
const uint8_t PY_mb_o     []={"Å¶à¸àŞ"};
const uint8_t PY_mb_ou    []={"Å·Å¸Å¹ÅºÅ»Å¼Å½ÇøÚ©âæê±ñî"};
const uint8_t PY_mb_pa    []={"°Ç°ÒÅ¾Å¿ÅÀÅÁÅÂÅÃİâèËóá"};
const uint8_t PY_mb_pai   []={"ÅÄÅÅÅÆÅÇÅÈÅÉÆÈÙ½İåßß"};
const uint8_t PY_mb_pan   []={"·¬ÅÊÅËÅÌÅÍÅÎÅÏÅĞÅÑó´õçÅÖŞÕãÜãİãúêÚñÈñá"};
const uint8_t PY_mb_pang  []={"°ò°õ°÷ÅÒÅÓÅÔÅÕÅÖáİäèó¦åÌ"};
const uint8_t PY_mb_pao   []={"Å×ÅØÅÙÅÚÅÛÅÜÅİáóâÒğåëãŞË"};
const uint8_t PY_mb_pei   []={"ÅŞÅßÅàÅáÅâÅãÅäÅåÅæàÎö¬àúì·ïÂõ¬"};
const uint8_t PY_mb_pen   []={"ÅçÅèäÔ"};
const uint8_t PY_mb_peng  []={"ÅõÅöÅéÅêÅëÅìÅíÅîÅïÅğÅñÅòÅóÅôâñÜ¡àØó²"};
const uint8_t PY_mb_pi    []={"±Ù·ñÅ÷ÅøÅùÅúÅûÅüÅıÅşÆ¡Æ¢Æ£Æ¤Æ¥Æ¦Æ§Ø§Æ¨Æ©ñ±õùØòÚéÚğÚüÛ¯ÛÜÛıÜ±ÜÅß¨àèâÏäÄæÇç¢èÁê¶î¢î¼îëñÔñâò·òç"};
const uint8_t PY_mb_pian  []={"±â±ãÆªÆ«Æ¬Æ­ÚÒæéçÂêúëİôæõä"};
const uint8_t PY_mb_piao  []={"Æ®Æ¯Æ°Æ±ÆÓØâæÎçÎî©àÑæôéèóª"};
const uint8_t PY_mb_pie   []={"Æ²Æ³Ø¯ÜÖë­"};
const uint8_t PY_mb_pin   []={"Æ´ÆµÆ¶Æ·Æ¸æ°æÉé¯êòò­"};
const uint8_t PY_mb_ping  []={"·ëÆ¹ÆºÆ»Æ¼Æ½Æ¾Æ¿ÆÀÆÁÙ·æ³èÒöÒ"};
const uint8_t PY_mb_po    []={"²´·±ÆÂÆÃÆÄÆÅÆÆÆÇÆÈÆÉÆÓØÏÚéÛ¶çêê·ë¶îÇîŞğ«óÍ"};
const uint8_t PY_mb_pou   []={"ÆÊÙöŞå"};
const uint8_t PY_mb_pu    []={"ÆÕ±¤±©¸¬ÆËÆÌÆÍÆÎÆÏÆĞÆÑÆÒÆÓÆÔÆÖÆ×ÆØÆÙÙéàÛäßõëå§è±ë«ïäïè"};
const uint8_t PY_mb_qi    []={"»ü¼©ÆÚÆÛÆÜÆİÆŞÆßÆàÆáÆâÆãÆäÆåÆæÆçÆèÆéÆêÆëÆìÆíáªÆîÆïÆğÆñÆòÆóÆôç÷çùè½ÆõÆöÆ÷ÆøÆùÆúÆûÆüÆıØ½ì÷í¬õè÷¢÷èØÁÙ¹ÛßÜ»ÜÎÜùİÂİİä¿æëç²êÈŞ­èçéÊì¥àÒá¨ãàíÓñıòÓòàôëôì"};
const uint8_t PY_mb_qia   []={"¿¨ÆşÇ¡Ç¢İÖñÊ÷Ä"};
const uint8_t PY_mb_qian  []={"Ç£Ç¤Ç¥Ç¦Ç§Ç¨Ç©ÇªÇ«Ç¬Ç­Ç®Ç¯Ç°Ç±Ç²Ç³Ç´ÇµÇ¶Ç·Ç¸ÏËÙ»ÙİÚäÜ·ÜÍÜçİ¡Şçá©ã¥ã»å¹åºå½ç×èıêùëÉí©îÔò¯óéôÇ"};
const uint8_t PY_mb_qiang []={"Ç¹ÇºÇ»Ç¼Ç½Ç¾Ç¿ÇÀõÄãŞê¨ìÁïÏïêãÜñßæÍéÉòŞôÇ"};
const uint8_t PY_mb_qiao  []={"¿ÇÇÁÇÂÇÃÇÄÇÅÇÆÇÇÇÈÇÉÇÊÇËÇÌÇÍÇÎÇÏÈ¸Ú½ÚÛÜñá½ã¾éÔõÎ÷³çØØäã¸íÍï¢"};
const uint8_t PY_mb_qie   []={"ÇĞÇÑÇÒÇÓÇÔÙ¤ã«ã»æªôòÛ§êüïÆóæ"};
const uint8_t PY_mb_qin   []={"ÇÕÇÖÇ×ÇØÇÙÇÚÇÛÇÜÇİÇŞÇßÜËŞìôÀßÄàºàßâÛéÕï·ñæñûòû"};
const uint8_t PY_mb_qing  []={"Ç×ÇàÇáÇâÇãÇäÇåÇæÇçÇèÇéÇêÇëÇìíàÜÜàõéÑïºòßóÀóäôìö¥öë÷ô"};
const uint8_t PY_mb_qiong []={"ÇíÇîñ·òËÚöÜäóÌõ¼öÆ"};
const uint8_t PY_mb_qiu   []={"³ğ¹êÇïÇğÇñÇòÇóÇôÇõÇöÙ´åÏôÃôÜåÙÛÏáìäĞé±êäò°òÇòøöú"};
const uint8_t PY_mb_qu    []={"Ç÷ÇøÇùÇúÇûÇüÇıÇşÈ¡È¢È£È¤È¥òĞ÷ñĞçÚ°Û¾ÛÉÜÄŞ¡Ş¾á«áéãÖè³êïë¬ëÔìîíáğ¶ñ³ó½ôğöÄ"};
const uint8_t PY_mb_quan  []={"È¦È§È¨È©ÈªÈ«È¬È­È®È¯È°Ú¹Üõòé÷Üáëãªç¹éúî°îıóÜ"};
const uint8_t PY_mb_que   []={"È±È²È³È´ÈµÈ¶È·È¸ã×ãÚí¨"};
const uint8_t PY_mb_qui   []={"÷ü"};  
const uint8_t PY_mb_qun   []={"È¹ÈºåÒ÷å"};
const uint8_t PY_mb_ran   []={"È»È¼È½È¾ÜÛòÅ÷×"};
const uint8_t PY_mb_rang  []={"È¿ÈÀÈÁÈÂÈÃìüğ¦"};
const uint8_t PY_mb_rao   []={"ÈÄÈÅÈÆÜéæ¬èã"};
const uint8_t PY_mb_re    []={"ÈÇÈÈßö"};
const uint8_t PY_mb_ren   []={"ÈÉÈÊÈËÈÌÈÍÈÎÈÏÈĞÈÑÈÒïşØéØğÜóİØâ¿éíñÅ"};
const uint8_t PY_mb_reng  []={"ÈÓÈÔ"};
const uint8_t PY_mb_ri    []={"ÈÕ"};
const uint8_t PY_mb_rong  []={"ÈÖÈ×ÈØÈÙÈÚÈÛÈÜÈİÈŞÈßáÉáõéÅëÀòî"};
const uint8_t PY_mb_rou   []={"ÈàÈáÈâôÛõå÷·"};
const uint8_t PY_mb_ru    []={"ÈãÈäÈåÈæÈçÈèÈéÈêÈëå¦ÈìäáİêàéŞ¸ä²çÈï¨ñàò¬"};
const uint8_t PY_mb_ruan  []={"ÈíÈîëÃ"};
const uint8_t PY_mb_rui   []={"ÈïÈğÈñÜÇî£èÄŞ¨ò¸"};
const uint8_t PY_mb_run   []={"ÈòÈó"};
const uint8_t PY_mb_ruo   []={"ÈôÈõÙ¼óè"};
const uint8_t PY_mb_sa    []={"ÈöÈ÷ÈøØ¦ØíìªëÛ"};
const uint8_t PY_mb_sai   []={"ÈùÈúÈûÈüàç"};
const uint8_t PY_mb_san   []={"ÈıÈşÉ¡É¢âÌë§ôÖ"};
const uint8_t PY_mb_sang  []={"É£É¤É¥Şúíßòª"};
const uint8_t PY_mb_sao   []={"É¦É§É¨É©ëığşÜ£çÒöş"};
const uint8_t PY_mb_se    []={"ÈûÉªÉ«É¬ØÄï¤ğ£"};
const uint8_t PY_mb_sen   []={"É­"};
const uint8_t PY_mb_seng  []={"É®"};
const uint8_t PY_mb_sha   []={"É¯É°É±É²É³É´ÉµÉ¶É·É¼ÏÃğğôÄö®öèßşì¦ï¡"};
const uint8_t PY_mb_shai  []={"É«É¸É¹"};
const uint8_t PY_mb_shan  []={"²ôµ¥ÉºÉ»É¼É½É¾É¿ÉÀÉÁÉÂÉÃÉÄÉÅÉÆÉÇÉÈÉÉÕ¤Ú¨ğŞô®óµõÇ÷­ØßÛ·ÛïÜÏáêäúæ©æÓæóëşìøîÌ÷Ô"};
const uint8_t PY_mb_shang []={"ÉÊÉËÉÌÉÍÉÎÉÏÉĞÉÑç´éäõüÛğìØ"};
const uint8_t PY_mb_shao  []={"ÇÊÉÒÉÓÉÔÉÕÉÖÉ×ÉØÉÙÉÚÉÛÉÜÛ¿Üæô¹äûè¼òÙóâ"};
const uint8_t PY_mb_she   []={"ÉİÉŞÉßÉàÉáÉâÉãÉäÉåÉæÉçÉè÷êÕÛØÇÙÜŞéâ¦äÜì¨î´îè"};
const uint8_t PY_mb_shei  []={"Ë­"}; 
const uint8_t PY_mb_shen  []={"²ÎÉéÉêÉëÉìÉíÉîÉïÉğÉñÉòÉóÉôÉõÉöÉ÷ÉøÊ²Ú·ÚÅİ·İØßÓäÉé©ëÏïòò×"};
const uint8_t PY_mb_sheng []={"³ËÉùÉúÉûÉüÉıÉşÊ¡Ê¢Ê£Ê¤Ê¥óÏáÓäÅêÉíò"};
const uint8_t PY_mb_shi   []={"ÊÇÊÂ³×Ê¦Ê®Ê¯Ê§Ê¨Ê©ÊªÊ«Ê¬Ê­Ê°Ê±Ê²Ê³Ê´ÊµÊ¶Ê·Ê¸Ê¹ÊºÊ»Ê¼Ê½Ê¾Ê¿ÊÀÊÁÊÃÊÄÊÅÊÆÊÈÊÉÊÊÊËÊÌÊÍÊÎÊÏÊĞÊÑÊÒÊÓÊÔËÆß±óÂÖ³ÖÅÚÖÛõİªİéâ»éøêÛìÂìêîæîèó§óßõ§õ¹öåöõ"};
const uint8_t PY_mb_shou  []={"ÊÕÊÖÊ×ÊØÊÙÊÚÊÛÊÜÊİÊŞŞĞá÷ç·ô¼"};
const uint8_t PY_mb_shu   []={"ÊßÊàÊáÊâÊãÊäÊåÊæÊçÊèÊéÊêÊëÊìÊíÊîÊïÊğÊñÊòÊóÊôÊõÊöÊ÷ÊøÊùÊúÊûÊüÊıÊşË¡Ù¿ÛÓãğäøæ­Ø­İÄŞóç£ë¨ëòì¯ïíïøñâ"};
const uint8_t PY_mb_shua  []={"Ë¢Ë£à§"};
const uint8_t PY_mb_shuai []={"ÂÊË¤Ë¥Ë¦Ë§ó°"};
const uint8_t PY_mb_shuan []={"Ë¨Ë©ãÅäÌ"};
const uint8_t PY_mb_shuang[]={"ËªË«Ë¬ãñæ×"};
const uint8_t PY_mb_shui  []={"Ë®Ë¯Ë°Ëµãß"};
const uint8_t PY_mb_shun  []={"Ë±Ë²Ë³Ë´"};
const uint8_t PY_mb_shuo  []={"ÊıËµË¶Ë·Ë¸İôŞ÷åùéÃîå"};
const uint8_t PY_mb_si    []={"Ë¹ËºË»Ë¼Ë½Ë¾Ë¿ËÀËÁËÂËÃËÄËÅËÆËÇËÈØËßĞÙ¹ÙîÛÌâ»ãáãôäùæ¦æáçÁìëïÈğ¸ñêòÏóÓ"};
const uint8_t PY_mb_song  []={"ËÉËÊËËËÌËÍËÎËÏËĞáÔâìã¤äÁñµáÂİ¿Ú¡"};
const uint8_t PY_mb_sou   []={"ËÑËÒËÓËÔÛÅà²âÈäÑì¬î¤ïËòôàÕŞ´"};
const uint8_t PY_mb_su    []={"ËÕËÖË×ËØËÙËÚËÛËÜËİËŞËßËàËõÙíãºä³óùöÕÚÕİøà¼ö¢"};
const uint8_t PY_mb_suan  []={"ËáËâËãâ¡"};
const uint8_t PY_mb_sui   []={"ËäËêËçËåËæËèËîËìËéËíËë"};
const uint8_t PY_mb_sun   []={"ËïËğËñ"};
const uint8_t PY_mb_suo   []={"ËòËóËôËõËöË÷ËøËùßïàÂàÊæ¶É¯èøêıíüôÈ"};
const uint8_t PY_mb_ta    []={"ËúËûËüËıËşÌ¡Ì¢í³Ì£Ì¤ÍØãËåİé½îèõÁäâ÷£äğ"};
const uint8_t PY_mb_tai   []={"Ì¥Ì¦Ì§Ì¨Ì©ÌªÌ«Ì¬Ì­õÌÛ¢Ş·ææëÄìÆîÑöØ"};
const uint8_t PY_mb_tan   []={"µ¯Ì®Ì¯Ì°Ì±Ì²Ì³Ì´ÌµÌ¶Ì·Ì¸Ì¹ÌºÌ»Ì¼Ì½Ì¾Ì¿ñûÛ°å£ê¼êæìşîãïÄïâ"};
const uint8_t PY_mb_tang  []={"ÌÀÌÁÌÂÌÃÌÄÌÅÌÆÌÇÌÈÌÉÌÊÌËÌÌÙÎâ¼äçè©éÌîõó«ï¦ïÛñíó¥ôÊõ±àû"};
const uint8_t PY_mb_tao   []={"ÌÍÌÎÌÏÌĞÌÑÌÒÌÓÌÔÌÕÌÖÌ×ß¶ßû÷Òä¬èºìâØ»"};
const uint8_t PY_mb_te    []={"ÌØß¯ìıï«"};
const uint8_t PY_mb_teng  []={"ÌÙÌÚÌÛëøÌÜ"};
const uint8_t PY_mb_ti    []={"ÌİÌŞÌßÌàÌáÌâÌãÌäÌåÌæÌçÌèÌéÌêÌëÙÃã©ç¾ÜèåÑç°ğÃñÓõ®"};
const uint8_t PY_mb_tian  []={"ÌìÌíÌîÌïÌğÌñÌòÌóéåŞİãÃãÙî±îäï»"};
const uint8_t PY_mb_tiao  []={"µ÷ÌôÌõÌöÌ÷ÌøÙ¬÷ØÜæìöï¢ñ»òèóÔôĞö¶öæ"};
const uint8_t PY_mb_tie   []={"ÌùÌúÌû÷Ñï°İÆ"};
const uint8_t PY_mb_ting  []={"ÌüÌıÌşÍ¡Í¢Í£Í¤Í¥Í¦Í§ÜğİãæÃîúòÑöªèè"};
const uint8_t PY_mb_tong  []={"Í©Í«Í¬Í­Í®Í¯Í°Í±Í²Í³Í´Ù¡Ù×ÜíâúäüÍªÙÚÛíàÌá¼íÅ"};
const uint8_t PY_mb_tou   []={"ÍµÍ¶Í·Í¸÷»î×Ùï"};
const uint8_t PY_mb_tu    []={"Í¹ÍºÍ»Í¼Í½Í¾Í¿ÍÀÍÁÍÂÍÃÜ¢İ±İËîÊõ©"};
const uint8_t PY_mb_tuan  []={"ÍÄÍÅŞÒåèî¶"};
const uint8_t PY_mb_tui   []={"ÍÆÍÇÍÈÍÉÍÊÍËìÕ"};
const uint8_t PY_mb_tun   []={"¶ÚÍÊÍÌÍÍÍÎâ½ëàÙÛêÕ"};
const uint8_t PY_mb_tuo   []={"ËµÍÏÍØÍĞÍÑÍÒÍÓÍÔÍÕÍÖÍ×ÍÙõÉØ±Ù¢ÛçãûèØèŞéÒíÈîèö¾óêõ¢âÕ"};
const uint8_t PY_mb_wa    []={"ÍÚÍÛÍÜÍİÍŞÍßÍàØôæ´ëğ"};
const uint8_t PY_mb_wai   []={"ÍáÍâáË"};
const uint8_t PY_mb_wan   []={"ÂûÍãÍäÍåÍæÍçÍèÍéÍêÍëÍìÍíÍîÍïÍğÍñÍòÍóØàÜ¹İ¸İÒæıòêçºçşëäîµ÷´"};
const uint8_t PY_mb_wang  []={"ÍôÍõÍöÍ÷ÍøÍùÍúÍûÍüÍıØèã¯÷ÍŞÌéş"};
const uint8_t PY_mb_wei   []={"ÎªÎ»Î½ÍşÎ¡Î¢Î£Î¤Î¬Î¥Î¦Î§Î¨Î©Î«Î­Î®Î¯Î°Î±Î²Î³Î´ÎµÎ¶Î·Î¸Î¹ÎºÎ¼Î¾Î¿ÎÀÙËÚÃÚóÛ×İÚŞ±àøá¡áËáÍâ¬åÔæ¸ğôì¿çâãÇâ«Úñãíä¢ä¶è¸ê¦ìĞôºöÛàí"};
const uint8_t PY_mb_wen   []={"ÎÊÎÄÎÅÎÆÎÁÎÂÎÃÎÇÎÈÎÉØØö©çäãÓãëè·"};
const uint8_t PY_mb_weng  []={"ÎËÎÌÎÍİîŞ³"};
const uint8_t PY_mb_wo    []={"ÎÒÎÕà¸ÎÏÎĞÎÑÎÓÎÔÎÖÎÎÙÁİ«á¢ö»ä×ë¿íÒ"};
const uint8_t PY_mb_wu    []={"ÎåÎïÎğÎñÎçÎèÎéÎäÎê¶ñÎòÎóØ£Î×ÎíÎØÎÙÎÚÎÛÎÜÎİÎŞÎßÎàÎáÎâÎãÎæÎëÎìÎîØõÚùğÄÛØÜÌßíâĞâäâèğÍğíòÚä´å»åÃåüæÄæğÚãè»êõì¶ìÉöÈ÷ù"};
const uint8_t PY_mb_xi    []={"Ï£Ï°Ï¦Ï·Ï¸ÎôÎõÎöÎ÷ÎøÎùÎúÎûÎüÎıÎşÏ¡õèÏ¢Ï¤Ï¥Ï§Ï¨ÏªÏ«Ï¬Ï®Ï¯Ï±Ï²Ï´ÏµÏ¶ôËğªåïæÒçôéØŞÉÜçÏ­Ï©Ï³ØÎÙÒÙâÚôÛ­İ¾İßİûßñáãâ¾ãÒä»äÀêØêêì¤ì¨ìäìùìûñ¶ñÓòáó£ó¬ôªô¸ôÑôâõµ÷û"};
const uint8_t PY_mb_xia   []={"Ï¹ÏºÏ»Ï¼Ï½Ï¾Ï¿ÏÀÏÁÏÂÏÃÏÄÏÅßÈáòåÚè¦èÔíÌóÁ÷ï"};
const uint8_t PY_mb_xian  []={"ÏÖÏÈÏÉÏÓÏÔÏÕÏ×ÏØÏÍÏ³Ï´ÏÆÏÇÏÊÏËÏÌÏÎÏÏÏĞÏÑÏÒÏÙÏÚÏÛÏÜÏİÏŞÏßÙşÜÈİ²Şºá­áıåßæµë¯ìŞììğÂğçğïò¹óÚôÌõ£õĞõÑö±"};
const uint8_t PY_mb_xiang []={"ÏñÏòÏó½µÏàÏáÏâÏãÏäÏæÏçÏèÏéÏêÏëÏìÏíÏîÏïÏğÏå÷ÏÜ¼İÙâÃâÔæøç½ó­öß"};
const uint8_t PY_mb_xiao  []={"Ğ¡ÏûĞ¤ÏôÏõÏöÏ÷ÏøÏùÏúÏüÏıÏşĞ¢Ğ£Ğ¥Ğ¦Ğ§ßØäìåĞóãóïæçç¯èÉèÕòÙ÷Ì"};
const uint8_t PY_mb_xie   []={"Ğ©ĞªĞ«Ğ¬Ğ­Ğ®Ğ¯Ğ°Ğ±Ğ²Ğ³Ğ´ĞµĞ¶Ğ·Ğ¸Ğ¹ĞºĞ»Ğ¼Ñª½âĞ¨Ò¶ÙÉÙôÛÄÛÆŞ¯ß¢â³âİäÍå¬åâç¥çÓé¿éÇò¡õóöÙ÷º"};
const uint8_t PY_mb_xin   []={"Ğ½Ğ¾Ğ¿ĞÀĞÁĞÂĞÃĞÄĞÅĞÆÜ°İ·ì§öÎê¿Ø¶âàïâ"};
const uint8_t PY_mb_xing  []={"ĞÒÊ¡ĞÇĞÈĞÉĞÊĞËĞÌĞÍĞÎĞÏĞĞĞÑĞÓĞÔĞÕâ¼ÚêÜôÜşß©ã¬íÊ"};
const uint8_t PY_mb_xiong []={"ĞÖĞ×ĞØĞÙĞÚĞÛĞÜÜº"};
const uint8_t PY_mb_xiu   []={"³ôËŞĞİĞŞĞßĞàĞáĞâĞãĞäĞåßİäåõ÷âÊá¶âÓğ¼÷Û"};
const uint8_t PY_mb_xu    []={"ĞøĞ÷ĞæĞçĞèĞéĞêĞëĞìĞíĞîĞïĞğĞñĞòĞóĞôĞõĞöÚ¼ìãÛÃÛ×Ş£äªä°äÓçïèòÓõñãíìôÚõ¯"};
const uint8_t PY_mb_xuan  []={"ĞşÑ¡ĞùĞúĞûäÖĞüĞıêÑÑ¤ìÅÑ£Ñ¢ÙØÚÎİæãùäöè¯é¸ìÓŞïíÛîçïàÈ¯"};
const uint8_t PY_mb_xue   []={"Ï÷Ñ¥Ñ¦Ñ§Ñ¨Ñ©Ñª÷¨ÚÊàåí´õ½"};
const uint8_t PY_mb_xun   []={"Ñ°Ñ®Ñ¸Ñ¶Ñ¯ÑµÑ«Ñ¬Ñ­Ñ±Ñ²Ñ³Ñ´Ñ·Û¨Û÷Ü÷Ş¹á¾áßõ¸öà¿£İ¡Ş¦â´Ùãâşä­ä±êÖñ¿"};
const uint8_t PY_mb_ya    []={"ÑÀÑ¿ÑÇÑÆÑ¹ÑÅÑºÑ»Ñ¼Ñ½Ñ¾ÑÂÑÃÑÄÑÈÔşØóÑÁÛëŞëá¬åÂæ«çğèâë²í¼íığéñâ"};
const uint8_t PY_mb_yan   []={"ÑÔÑİÑéÑáÑÏÑØÑ×ÑàÑÊÑËÑÙÑÚÑÛÑÌÑÍÑÎÑĞÑÒÑÓÑÕÑÖÑÜÑŞÑßÑâÑãÑäÑÉÑåÑæÑçÑèÑÑãÆåûæÌëÙëçìÍâûÙ²ÙÈÇ¦ÒóØÉØÍØßÙğÚ¥ÚİÚçÛ±Û³Ü¾İÎáÃ÷ÊãÕäÎäÙçüéÜêÌî»óÛõ¦÷Ğ÷ú÷ü"};
const uint8_t PY_mb_yang  []={"ÑëÑöÑòÑóÑôÑøÑùÑîÑïí¦ÑêÑìÑíÑğÑõÑñÑ÷Ñúáàâóãóì¾ìÈòÕ÷±"};
const uint8_t PY_mb_yao   []={"ÒªÑûÒ§Ò©ÑüÑıÒ¡Ò¢ëÈñºÒ£Ò¤Ò¥Ò¦Ò¨Ò«Ô¿Ø²Ø³çÛßºÑşÄöÅ±½ÄáÅáÊáæçòèÃé÷ê×ï¢ğÎôí÷¥"};
const uint8_t PY_mb_ye    []={"Ò²Ò³ÒµÒ¶Ò¹ÒºÒ¬Ò­Ò®Ò¯Ò°Ò±Ò´Ò·Ò¸Ğ°ÑÊÚËÖÑØÌÚşŞŞçğêÊìÇîô"};
const uint8_t PY_mb_yi    []={"Ò»ÒÒÒÑÒÔÒäÒåÒéÒêÒëÒìÒæÒ¼Ò½Ò¾Ò¿ÒÀÒÁÒÂÒÃÒÄÒÅÒÆÒÇÒÈÒÉÒÊÒËÒÌÒÍÒÎÒÏÒĞÒÓÒÕÒÖÒ×ÒØÒÙÒÚÒÛÒÜÒİÒŞÒßÒàÒáÒâÒãÒçÒèÒíÒî°¬Î²ÒïØ×ØæØıÙ«Ú±ÚâÛİÛüÜ²ÜÓÜèŞ²ŞÄŞÈŞÚß®ß½ß×ßŞàæá»áÚâ¢âÂâøâùã¨äôåÆæäçËéìéóêİì¥ì½ìÚíôîÆîèï×ïîğêğùñ¯ñ´ñÂòæô¯ôàôèôı÷ğ"};
const uint8_t PY_mb_yin   []={"ÒüÒıÓ¡ÒğÒñÒòÒóÒôÒõÒöÒ÷ÒøÒùÒúÒûÒşö¸Ø·ò¾Û´ÛÈÛóÜ§ÜáßÅà³áşâ¹ä¦äÎë³î÷ñ«ñ¿ö¯"};
const uint8_t PY_mb_ying  []={"Ó³Ó°Ó¢Ó¨Ó©ÓªÓ«Ó£Ó¤Ó¥Ó¦Ó§Ó¬Ó­Ó®Ó¯Ó±Ó²ÙøİºİÓğĞäëå­äŞçøÛ«ÜãÜşİöŞüàÓâßè¬éºëôñ¨ò£ó¿"};
const uint8_t PY_mb_yo    []={"Ó´Óıà¡"};
const uint8_t PY_mb_yong  []={"ÓÃÓµÓ¶ÓÂÓ¿Ó·Ó¸Ó¹ÓºÓ»Ó¼Ó½Ó¾ÓÀÓÁÙ¸ÛÕÜ­à¯ã¼çßïŞğ®÷«÷Ó"};
const uint8_t PY_mb_you   []={"ÓÈÓĞÓÖÓÕÓ×ÓÑÓÒÓÓÓÄÓÅÓÆÓÇÓÉÓÊÓËÓÌÓÍÓÎÓÏÓÔßÏğàöÏ÷î÷øòÄØüØÕÙ§İ¬İ¯İµŞÌàóå¶èÖéàë»îğòÊòöòøôí"};
const uint8_t PY_mb_yu    []={"ÓàÓëÓÚÓèÓîÓñÓêÓıÓşÔ¡ÓãÓØÓÙÓÛÓİÓŞÓßÓáÓâÓäÓåÓæÓçÓéÓìÓíÓïÓğÓòÓóÓôÓõÓöÓ÷ÓøÓùÓúÓÜÓûÓüÔ¢Ô£Ô¤Ô¥Ô¦óÄØ¹ÚÄì¶ÚÍÎµÎ¾Ø®ØñÙ¶İÇİÒİ÷ŞíàôàöáÎáüâÀâÅâ×ãĞå÷åıæ¥æúè¤êÅêìëéì£ìÏìÙìÛí±í²îÚğÁğÖğõğöñ¾ñÁòâòõô§ô¨ö§ö¹"};
const uint8_t PY_mb_yuan  []={"Ô­ÔªÔ°Ô±Ô²Ô´ÔµÔ¶Ô¸Ô¹ÔºÔ§Ô¨Ô©Ô«Ô¬Ô®Ô¯Ô³Ô·æÂÜ«Ü¾Şòà÷ãäè¥éÚë¼íóğ°ó¢óîö½"};
const uint8_t PY_mb_yue   []={"ÔÂÔÃÔÄÀÖËµÔ»Ô¼Ô½Ô¾Ô¿ÔÀÔÁÙßßÜå®èİéĞë¾îá"};
const uint8_t PY_mb_yun   []={"ÔÆÔ±ÔÊÔËÔÎÔÅÔÈÔÉÔÌÔÍìÙÔÏÔĞëµéæÜ¿ÔÇÛ©áñã¢ã³ç¡è¹êÀóŞ"};
const uint8_t PY_mb_za    []={"ÔÑÔÒÔÓÔúÕ¦ßÆŞÙ"};
const uint8_t PY_mb_zai   []={"ÔÙÔÚÔÔÔÕÔÖÔ×ÔØáÌçŞ"};
const uint8_t PY_mb_zan   []={"ÔÛÔÜÔİÔŞêÃô¢ŞÙè¶ôØôõöÉ"};
const uint8_t PY_mb_zang  []={"²ØÔßÔàÔáæàê°"};
const uint8_t PY_mb_zao   []={"ÔæÔâÔçÔìÔíÔîÔãÔäÔèÔêÔëÔïÔåÔéßğ"};
const uint8_t PY_mb_ze    []={"ÔğÔñÔòÔóÕ¦ØÆØÓßõàıåÅê¾óĞóåô·"};
const uint8_t PY_mb_zei   []={"Ôô"};
const uint8_t PY_mb_zen   []={"ÔõÚÚ"};
const uint8_t PY_mb_zeng  []={"ÔöÔ÷ÔøÔùçÕêµîÀï­"};
const uint8_t PY_mb_zha   []={"ÔúÕ¢²éÔûÔüÔıÔşÕ¡Õ£Õ¤Õ¥Õ¦Õ§Õ¨Õ©ß¸ßå×õŞêòÆßîà©é«íÄğäö´÷ş"};
const uint8_t PY_mb_zhai  []={"Õ¬Õ­Õ®µÔÔñÕªÕ«Õ¯íÎñ©"};
const uint8_t PY_mb_zhan  []={"Õ¼Õ½Õ¾Õ¹Õ´ÕÀÕ°Õ±Õ²Õ³ÕµÕ¶Õ·Õ¸Õº²üÕ»Õ¿ÚŞŞøæöì¹"};
const uint8_t PY_mb_zhang []={"ÕÅÕÉÕÌÕÍÕÈÕÁÕÂÕÃÕÄÕÆÕÇÕÊÕË³¤ÕÎÕÏá¤áÖâ¯ó¯ØëÛµæÑè°"};
const uint8_t PY_mb_zhao  []={"ÕÒÕÙ×¦×ÅÕ×³¯ÕĞÕÑÚ¯ÕÓÕÔÕÕÕÖÕØîÈóÉßúèş"};
const uint8_t PY_mb_zhe   []={"ÕÚÕÛÕÜÕİÕŞÕßÕàÕáÕâÕã×ÅÚØß¡èÏéüíİğÑñŞòØô÷"};
const uint8_t PY_mb_zhen  []={"ÕæÕêÕëÕğÕñÕïÕóÕòÕìÕíÕäÕîÕåÕçóğÕéÖ¡ÛÚÕèİèä¥äÚçÇèåé©é»éôêâëÓëŞìõî³ğ¡ğ²"};
const uint8_t PY_mb_zheng []={"ÕıÖ¤ÕôÕõÕöÕ÷ÕøÕùÕúÕûÕüÕşÖ¢Ö£Úºá¿áçîÛï£óİöë"};
const uint8_t PY_mb_zhi   []={"ÖÊÖÃÖÆÖÎÖ§Ö»Ê¶Ö´ÖµÖ¹ÖÁÖ¥Ö®Ö­Ö¼Ö½Ö¾Ö¦ÖªÖ«Ö¬Ö¯Ö°Ö±Ö²Ö³Ö¶Ö·Ö¸ÖºÖ¿ÖÀÖÂÖÄÖÅÖÇÖÈÖÉÖ¨Ö©ÖËÖÌÖÍÖÏè×ÜÆØ´ÚìÛ¤ÛúŞıàùáçâºâååéåëæïèÎèÙèäéòéùêŞëÕëùìíìóíéïôğºğëòÎôêõ¥õÅõÙõÜõôö£"};
const uint8_t PY_mb_zhong []={"ÖĞÖÚÖÒÖÓÖÔÖÕÖÖÖ×ÖØÖÙÖÑÚ£âìïñó®ô±õà"};
const uint8_t PY_mb_zhou  []={"ÖÛÖÜÖİÖŞÖßÖàÖáÖâÖãÖäÖåÖæÖçÖèİ§ßúæ¨æûç§ëĞíØô¦ôíôü"};
const uint8_t PY_mb_zhu   []={"Ö÷×¡×¢×£ÖñÖéÖêÖëÖìÖíÖîÖïÖğÖòÖóÖôÖõÖöÖøÖùÖúÖûÖüÖıÖş×¤ØùóÃóçÙªÊôÊõÛ¥ÜÑÜïä¨ä¾äóèÌéÆéÍìÄîùğæğññÒô¶ôãõî÷æØ¼"};
const uint8_t PY_mb_zhua  []={"×¥×¦ÎÎ"};
const uint8_t PY_mb_zhuai []={"×§×ª"};
const uint8_t PY_mb_zhuan []={"´«×¨×©×ª×«×¬×­ßùâÍãçò§"};
const uint8_t PY_mb_zhuang[]={"´±×®×¯×°×±×²×³×´ŞÊí°"};
const uint8_t PY_mb_zhui  []={"×µ×¶×·×¸×¹×ºã·æíçÄö¿"};
const uint8_t PY_mb_zhun  []={"×»×¼â½ëÆñ¸"};
const uint8_t PY_mb_zhuo  []={"×Å×½×¾×¿×À×Æ×Â×Ç×Ã×Á×ÄÙ¾ÚÂßªä·äÃåªìÌìúí½ïí"};
const uint8_t PY_mb_zi    []={"×Ô×Ó×Ö×Ğ×È×É×Ê×Ë×Ì×Í×Î×Ï×Ñ×Ò×Õö·æ¢Ö¨áÑÚÑÜëæÜç»è÷ê¢êßí§íöïÅïöñèóÊôÒôôõşö¤öö÷Ú"};
const uint8_t PY_mb_zong  []={"×Ú×Û×Ü×××Ø×Ù×İôÕÙÌèÈëê"};
const uint8_t PY_mb_zou   []={"×ß×à×á×ŞÚÁÚîÛ¸æãöí"};
const uint8_t PY_mb_zu    []={"×ã×â×æ×ç×è×é×ä×åÙŞİÏïß"};
const uint8_t PY_mb_zuan  []={"×êß¬×ëçÚõò"};
const uint8_t PY_mb_zui   []={"×î×ï×ì×íŞ©õş"};
const uint8_t PY_mb_zun   []={"×ğ×ñé×÷®ß¤"};
const uint8_t PY_mb_zuo   []={"×ó×ô×ö×÷×ø×ù×ò´éßò×õÚè×ÁàÜâôëÑìñíÄõ¡"};

//Æ´ÒôË÷Òı±í
const py_index py_index3[]=
{
{"" ,"",(uint8_t*)PY_mb_space},
{"2","a",(uint8_t*)PY_mb_a},
{"3","e",(uint8_t*)PY_mb_e},
{"6","o",(uint8_t*)PY_mb_o},
{"24","ai",(uint8_t*)PY_mb_ai},
{"26","an",(uint8_t*)PY_mb_an},
{"26","ao",(uint8_t*)PY_mb_ao},
{"22","ba",(uint8_t*)PY_mb_ba},
{"24","bi",(uint8_t*)PY_mb_bi},
{"26","bo",(uint8_t*)PY_mb_bo},
{"28","bu",(uint8_t*)PY_mb_bu},
{"22","ca",(uint8_t*)PY_mb_ca},
{"23","ce",(uint8_t*)PY_mb_ce},
{"24","ci",(uint8_t*)PY_mb_ci},
{"28","cu",(uint8_t*)PY_mb_cu},
{"32","da",(uint8_t*)PY_mb_da},
{"33","de",(uint8_t*)PY_mb_de},
{"34","di",(uint8_t*)PY_mb_di},
{"38","du",(uint8_t*)PY_mb_du},
{"36","en",(uint8_t*)PY_mb_en},
{"37","er",(uint8_t*)PY_mb_er},
{"32","fa",(uint8_t*)PY_mb_fa},
{"36","fo",(uint8_t*)PY_mb_fo},
{"38","fu",(uint8_t*)PY_mb_fu},
{"42","ha",(uint8_t*)PY_mb_ha},
{"42","ga",(uint8_t*)PY_mb_ga},
{"43","ge",(uint8_t*)PY_mb_ge},
{"43","he",(uint8_t*)PY_mb_he},
{"48","gu",(uint8_t*)PY_mb_gu},
{"48","hu",(uint8_t*)PY_mb_hu},
{"54","ji",(uint8_t*)PY_mb_ji},
{"58","ju",(uint8_t*)PY_mb_ju},
{"52","ka",(uint8_t*)PY_mb_ka},
{"53","ke",(uint8_t*)PY_mb_ke},
{"58","ku",(uint8_t*)PY_mb_ku},
{"52","la",(uint8_t*)PY_mb_la},
{"53","le",(uint8_t*)PY_mb_le},
{"54","li",(uint8_t*)PY_mb_li},
{"58","lu",(uint8_t*)PY_mb_lu},
{"58","lv",(uint8_t*)PY_mb_lv},
{"62","ma",(uint8_t*)PY_mb_ma},
{"63","me",(uint8_t*)PY_mb_me},
{"64","mi",(uint8_t*)PY_mb_mi},
{"66","mo",(uint8_t*)PY_mb_mo},
{"68","mu",(uint8_t*)PY_mb_mu},
{"62","na",(uint8_t*)PY_mb_na},
{"63","ne",(uint8_t*)PY_mb_ne},
{"64","ni",(uint8_t*)PY_mb_ni},
{"68","nu",(uint8_t*)PY_mb_nu},
{"68","nv",(uint8_t*)PY_mb_nv},
{"68","ou",(uint8_t*)PY_mb_ou},
{"72","pa",(uint8_t*)PY_mb_pa},
{"74","pi",(uint8_t*)PY_mb_pi},
{"76","po",(uint8_t*)PY_mb_po},
{"78","pu",(uint8_t*)PY_mb_pu},
{"74","qi",(uint8_t*)PY_mb_qi},
{"78","qu",(uint8_t*)PY_mb_qu},
{"73","re",(uint8_t*)PY_mb_re},
{"74","ri",(uint8_t*)PY_mb_ri},
{"78","ru",(uint8_t*)PY_mb_ru},
{"72","sa",(uint8_t*)PY_mb_sa},
{"73","se",(uint8_t*)PY_mb_se},
{"74","si",(uint8_t*)PY_mb_si},
{"78","su",(uint8_t*)PY_mb_su},
{"82","ta",(uint8_t*)PY_mb_ta},
{"83","te",(uint8_t*)PY_mb_te},
{"84","ti",(uint8_t*)PY_mb_ti},
{"88","tu",(uint8_t*)PY_mb_tu},
{"92","wa",(uint8_t*)PY_mb_wa},
{"96","wo",(uint8_t*)PY_mb_wo},
{"98","wu",(uint8_t*)PY_mb_wu},
{"94","xi",(uint8_t*)PY_mb_xi},
{"98","xu",(uint8_t*)PY_mb_xu},
{"92","ya",(uint8_t*)PY_mb_ya},
{"93","ye",(uint8_t*)PY_mb_ye},
{"94","yi",(uint8_t*)PY_mb_yi},
{"96","yo",(uint8_t*)PY_mb_yo},
{"98","yu",(uint8_t*)PY_mb_yu},
{"92","za",(uint8_t*)PY_mb_za},
{"93","ze",(uint8_t*)PY_mb_ze},
{"94","zi",(uint8_t*)PY_mb_zi},
{"98","zu",(uint8_t*)PY_mb_zu},
{"264","ang",(uint8_t*)PY_mb_ang},
{"224","bai",(uint8_t*)PY_mb_bai},
{"226","ban",(uint8_t*)PY_mb_ban},
{"226","bao",(uint8_t*)PY_mb_bao},
{"234","bei",(uint8_t*)PY_mb_bei},
{"236","ben",(uint8_t*)PY_mb_ben},
{"243","bie",(uint8_t*)PY_mb_bie},
{"246","bin",(uint8_t*)PY_mb_bin},
{"224","cai",(uint8_t*)PY_mb_cai},
{"226","can",(uint8_t*)PY_mb_can},
{"226","cao",(uint8_t*)PY_mb_cao},
{"242","cha",(uint8_t*)PY_mb_cha},
{"243","che",(uint8_t*)PY_mb_che},
{"244","chi",(uint8_t*)PY_mb_chi},
{"248","chu",(uint8_t*)PY_mb_chu},
{"268","cou",(uint8_t*)PY_mb_cou},
{"284","cui",(uint8_t*)PY_mb_cui},
{"286","cun",(uint8_t*)PY_mb_cun},
{"286","cuo",(uint8_t*)PY_mb_cuo},
{"324","dai",(uint8_t*)PY_mb_dai},
{"326","dan",(uint8_t*)PY_mb_dan},
{"326","dao",(uint8_t*)PY_mb_dao},
{"334","dei",(uint8_t*)PY_mb_dei},
{"343","die",(uint8_t*)PY_mb_die},
{"348","diu",(uint8_t*)PY_mb_diu},
{"368","dou",(uint8_t*)PY_mb_dou},
{"384","dui",(uint8_t*)PY_mb_dui},
{"386","dun",(uint8_t*)PY_mb_dun},
{"386","duo",(uint8_t*)PY_mb_duo},								
{"326","fan",(uint8_t*)PY_mb_fan},
{"334","fei",(uint8_t*)PY_mb_fei},
{"336","fen",(uint8_t*)PY_mb_fen},
{"368","fou",(uint8_t*)PY_mb_fou},
{"424","gai",(uint8_t*)PY_mb_gai},
{"426","gan",(uint8_t*)PY_mb_gan},
{"426","gao",(uint8_t*)PY_mb_gao},
{"434","gei",(uint8_t*)PY_mb_gei},
{"436","gen",(uint8_t*)PY_mb_gan},
{"468","gou",(uint8_t*)PY_mb_gou},
{"482","gua",(uint8_t*)PY_mb_gua},
{"484","gui",(uint8_t*)PY_mb_gui},
{"486","gun",(uint8_t*)PY_mb_gun},
{"486","guo",(uint8_t*)PY_mb_guo},
{"424","hai",(uint8_t*)PY_mb_hai},
{"426","han",(uint8_t*)PY_mb_han},
{"426","hao",(uint8_t*)PY_mb_hao},
{"434","hei",(uint8_t*)PY_mb_hei},
{"436","hen",(uint8_t*)PY_mb_hen},
{"468","hou",(uint8_t*)PY_mb_hou},
{"482","hua",(uint8_t*)PY_mb_hua},
{"484","hui",(uint8_t*)PY_mb_hui},
{"486","hun",(uint8_t*)PY_mb_hun},
{"486","huo",(uint8_t*)PY_mb_huo},
{"542","jia",(uint8_t*)PY_mb_jia},
{"543","jie",(uint8_t*)PY_mb_jie},
{"546","jin",(uint8_t*)PY_mb_jin},
{"548","jiu",(uint8_t*)PY_mb_jiu},
{"583","jue",(uint8_t*)PY_mb_jue},
{"586","jun",(uint8_t*)PY_mb_jun},
{"524","kai",(uint8_t*)PY_mb_kai},
{"526","kan",(uint8_t*)PY_mb_kan},
{"526","kao",(uint8_t*)PY_mb_kao},
{"536","ken",(uint8_t*)PY_mb_ken},
{"568","kou",(uint8_t*)PY_mb_kou},
{"582","kua",(uint8_t*)PY_mb_kua},
{"584","kui",(uint8_t*)PY_mb_kui},
{"586","kun",(uint8_t*)PY_mb_kun},
{"586","kuo",(uint8_t*)PY_mb_kuo},
{"524","lai",(uint8_t*)PY_mb_lai},
{"526","lan",(uint8_t*)PY_mb_lan},
{"526","lao",(uint8_t*)PY_mb_lao},
{"534","lei",(uint8_t*)PY_mb_lei},
{"543","lie",(uint8_t*)PY_mb_lie},
{"546","lin",(uint8_t*)PY_mb_lin},
{"548","liu",(uint8_t*)PY_mb_liu},
{"568","lou",(uint8_t*)PY_mb_lou},
{"583","lue",(uint8_t*)PY_mb_lue},
{"586","lun",(uint8_t*)PY_mb_lun},
{"586","luo",(uint8_t*)PY_mb_luo},
{"624","mai",(uint8_t*)PY_mb_mai},
{"626","man",(uint8_t*)PY_mb_man},
{"626","mao",(uint8_t*)PY_mb_mao},
{"634","mei",(uint8_t*)PY_mb_mei},
{"636","men",(uint8_t*)PY_mb_men},
{"643","mie",(uint8_t*)PY_mb_mie},
{"646","min",(uint8_t*)PY_mb_min},
{"648","miu",(uint8_t*)PY_mb_miu},
{"668","mou",(uint8_t*)PY_mb_mou},
{"624","nai",(uint8_t*)PY_mb_nai},
{"626","nan",(uint8_t*)PY_mb_nan},
{"626","nao",(uint8_t*)PY_mb_nao},
{"634","nei",(uint8_t*)PY_mb_nei},
{"636","nen",(uint8_t*)PY_mb_nen},
{"643","nie",(uint8_t*)PY_mb_nie},
{"646","nin",(uint8_t*)PY_mb_nin},
{"648","niu",(uint8_t*)PY_mb_niu},
{"683","nue",(uint8_t*)PY_mb_nue},
{"686","nuo",(uint8_t*)PY_mb_nuo},
{"724","pai",(uint8_t*)PY_mb_pai},
{"726","pan",(uint8_t*)PY_mb_pan},
{"726","pao",(uint8_t*)PY_mb_pao},
{"734","pei",(uint8_t*)PY_mb_pei},
{"736","pen",(uint8_t*)PY_mb_pen},
{"743","pie",(uint8_t*)PY_mb_pie},
{"746","pin",(uint8_t*)PY_mb_pin},
{"768","pou",(uint8_t*)PY_mb_pou},
{"742","qia",(uint8_t*)PY_mb_qia},
{"743","qie",(uint8_t*)PY_mb_qie},
{"746","qin",(uint8_t*)PY_mb_qin},
{"748","qiu",(uint8_t*)PY_mb_qiu},
{"783","que",(uint8_t*)PY_mb_que},
{"786","qun",(uint8_t*)PY_mb_qun},
{"726","ran",(uint8_t*)PY_mb_ran},
{"726","rao",(uint8_t*)PY_mb_rao},
{"736","ren",(uint8_t*)PY_mb_ren},
{"768","rou",(uint8_t*)PY_mb_rou},
{"784","rui",(uint8_t*)PY_mb_rui},
{"786","run",(uint8_t*)PY_mb_run},
{"786","ruo",(uint8_t*)PY_mb_ruo},
{"724","sai",(uint8_t*)PY_mb_sai},
{"726","sao",(uint8_t*)PY_mb_sao},
{"726","san",(uint8_t*)PY_mb_san},
{"736","sen",(uint8_t*)PY_mb_sen},
{"742","sha",(uint8_t*)PY_mb_sha},
{"743","she",(uint8_t*)PY_mb_she},
{"744","shi",(uint8_t*)PY_mb_shi},
{"748","shu",(uint8_t*)PY_mb_shu},
{"768","sou",(uint8_t*)PY_mb_sou},
{"784","sui",(uint8_t*)PY_mb_sui},
{"786","sun",(uint8_t*)PY_mb_sun},
{"786","suo",(uint8_t*)PY_mb_suo},
{"824","tai",(uint8_t*)PY_mb_tai},
{"826","tan",(uint8_t*)PY_mb_tan},
{"826","tao",(uint8_t*)PY_mb_tao},
{"843","tie",(uint8_t*)PY_mb_tie},
{"868","tou",(uint8_t*)PY_mb_tou},
{"884","tui",(uint8_t*)PY_mb_tui},
{"886","tun",(uint8_t*)PY_mb_tun},
{"886","tuo",(uint8_t*)PY_mb_tuo},
{"924","wai",(uint8_t*)PY_mb_wai},
{"926","wan",(uint8_t*)PY_mb_wan},
{"934","wei",(uint8_t*)PY_mb_wei},
{"936","wen",(uint8_t*)PY_mb_wen},
{"942","xia",(uint8_t*)PY_mb_xia},
{"943","xie",(uint8_t*)PY_mb_xie},
{"946","xin",(uint8_t*)PY_mb_xin},
{"948","xiu",(uint8_t*)PY_mb_xiu},
{"983","xue",(uint8_t*)PY_mb_xue},
{"986","xun",(uint8_t*)PY_mb_xun},
{"926","yan",(uint8_t*)PY_mb_yan},
{"926","yao",(uint8_t*)PY_mb_yao},
{"946","yin",(uint8_t*)PY_mb_yin},
{"968","you",(uint8_t*)PY_mb_you},
{"983","yue",(uint8_t*)PY_mb_yue},
{"986","yun",(uint8_t*)PY_mb_yun},
{"924","zai",(uint8_t*)PY_mb_zai},
{"926","zan",(uint8_t*)PY_mb_zan},
{"926","zao",(uint8_t*)PY_mb_zao},
{"934","zei",(uint8_t*)PY_mb_zei},
{"936","zen",(uint8_t*)PY_mb_zen},
{"942","zha",(uint8_t*)PY_mb_zha},
{"943","zhe",(uint8_t*)PY_mb_zhe},
{"944","zhi",(uint8_t*)PY_mb_zhi},
{"948","zhu",(uint8_t*)PY_mb_zhu},
{"968","zou",(uint8_t*)PY_mb_zou},
{"984","zui",(uint8_t*)PY_mb_zui},
{"986","zun",(uint8_t*)PY_mb_zun},
{"986","zuo",(uint8_t*)PY_mb_zuo},
{"2264","bang",(uint8_t*)PY_mb_bang},
{"2364","beng",(uint8_t*)PY_mb_beng},
{"2426","bian",(uint8_t*)PY_mb_bian},
{"2426","biao",(uint8_t*)PY_mb_biao},
{"2464","bing",(uint8_t*)PY_mb_bing},
{"2264","cang",(uint8_t*)PY_mb_cang},
{"2364","ceng",(uint8_t*)PY_mb_ceng},
{"2424","chai",(uint8_t*)PY_mb_chai},
{"2426","chan",(uint8_t*)PY_mb_chan},
{"2426","chao",(uint8_t*)PY_mb_chao},
{"2436","chen",(uint8_t*)PY_mb_chen},
{"2468","chou",(uint8_t*)PY_mb_chou},
{"2484","chuai",(uint8_t*)PY_mb_chuai},
{"2484","chui",(uint8_t*)PY_mb_chui},
{"2486","chun",(uint8_t*)PY_mb_chun},
{"2486","chuo",(uint8_t*)PY_mb_chuo},
{"2664","cong",(uint8_t*)PY_mb_cong},
{"2826","cuan",(uint8_t*)PY_mb_cuan},
{"3264","dang",(uint8_t*)PY_mb_dang},
{"3364","deng",(uint8_t*)PY_mb_deng},
{"3426","dian",(uint8_t*)PY_mb_dian},
{"3426","diao",(uint8_t*)PY_mb_diao},
{"3464","ding",(uint8_t*)PY_mb_ding},
{"3664","dong",(uint8_t*)PY_mb_dong},
{"3826","duan",(uint8_t*)PY_mb_duan},
{"3264","fang",(uint8_t*)PY_mb_fang},
{"3364","feng",(uint8_t*)PY_mb_feng},
{"4264","gang",(uint8_t*)PY_mb_gang},
{"4364","geng",(uint8_t*)PY_mb_geng},
{"4664","gong",(uint8_t*)PY_mb_gong},
{"4824","guai",(uint8_t*)PY_mb_guai},
{"4826","guan",(uint8_t*)PY_mb_guan},
{"4264","hang",(uint8_t*)PY_mb_hang},
{"4364","heng",(uint8_t*)PY_mb_heng},
{"4664","hong",(uint8_t*)PY_mb_hong},
{"4823","huai",(uint8_t*)PY_mb_huai},
{"4826","huan",(uint8_t*)PY_mb_huan},
{"5426","jian",(uint8_t*)PY_mb_jian},
{"5426","jiao",(uint8_t*)PY_mb_jiao},
{"5464","jing",(uint8_t*)PY_mb_jing},
{"5826","juan",(uint8_t*)PY_mb_juan},
{"5264","kang",(uint8_t*)PY_mb_kang},
{"5364","keng",(uint8_t*)PY_mb_keng},
{"5664","kong",(uint8_t*)PY_mb_kong},
{"5824","kuai",(uint8_t*)PY_mb_kuai},
{"5826","kuan",(uint8_t*)PY_mb_kuan},
{"5264","lang",(uint8_t*)PY_mb_lang},
{"5366","leng",(uint8_t*)PY_mb_leng},
{"5426","lian",(uint8_t*)PY_mb_lian},
{"5426","liao",(uint8_t*)PY_mb_liao},
{"5464","ling",(uint8_t*)PY_mb_ling},
{"5664","long",(uint8_t*)PY_mb_long},
{"5826","luan",(uint8_t*)PY_mb_luan},
{"6264","mang",(uint8_t*)PY_mb_mang},
{"6364","meng",(uint8_t*)PY_mb_meng},
{"6426","mian",(uint8_t*)PY_mb_mian},
{"6426","miao",(uint8_t*)PY_mb_miao},
{"6464","ming",(uint8_t*)PY_mb_ming},
{"6264","nang",(uint8_t*)PY_mb_nang},
{"6364","neng",(uint8_t*)PY_mb_neng},
{"6426","nian",(uint8_t*)PY_mb_nian},
{"6426","niao",(uint8_t*)PY_mb_niao},
{"6464","ning",(uint8_t*)PY_mb_ning},
{"6664","nong",(uint8_t*)PY_mb_nong},
{"6826","nuan",(uint8_t*)PY_mb_nuan},
{"7264","pang",(uint8_t*)PY_mb_pang},
{"7364","peng",(uint8_t*)PY_mb_peng},
{"7426","pian",(uint8_t*)PY_mb_pian},
{"7426","piao",(uint8_t*)PY_mb_piao},
{"7464","ping",(uint8_t*)PY_mb_ping},
{"7426","qian",(uint8_t*)PY_mb_qian},
{"7426","qiao",(uint8_t*)PY_mb_qiao},
{"7464","qing",(uint8_t*)PY_mb_qing},
{"7826","quan",(uint8_t*)PY_mb_quan},
{"7264","rang",(uint8_t*)PY_mb_rang},
{"7364","reng",(uint8_t*)PY_mb_reng},
{"7664","rong",(uint8_t*)PY_mb_rong},
{"7826","ruan",(uint8_t*)PY_mb_ruan},
{"7264","sang",(uint8_t*)PY_mb_sang},
{"7364","seng",(uint8_t*)PY_mb_seng},
{"7424","shai",(uint8_t*)PY_mb_shai},
{"7426","shan",(uint8_t*)PY_mb_shan},
{"7426","shao",(uint8_t*)PY_mb_shao},
{"7434","shei",(uint8_t*)PY_mb_shei},
{"7436","shen",(uint8_t*)PY_mb_shen},    
{"7468","shou",(uint8_t*)PY_mb_shou},
{"7482","shua",(uint8_t*)PY_mb_shua},
{"7484","shui",(uint8_t*)PY_mb_shui},
{"7486","shun",(uint8_t*)PY_mb_shun},
{"7486","shuo",(uint8_t*)PY_mb_shuo},
{"7664","song",(uint8_t*)PY_mb_song},
{"7826","suan",(uint8_t*)PY_mb_suan},
{"8264","tang",(uint8_t*)PY_mb_tang},
{"8364","teng",(uint8_t*)PY_mb_teng},
{"8426","tian",(uint8_t*)PY_mb_tian},
{"8426","tiao",(uint8_t*)PY_mb_tiao},
{"8464","ting",(uint8_t*)PY_mb_ting},
{"8664","tong",(uint8_t*)PY_mb_tong},
{"8826","tuan",(uint8_t*)PY_mb_tuan},
{"9264","wang",(uint8_t*)PY_mb_wang},
{"9364","weng",(uint8_t*)PY_mb_weng},
{"9426","xian",(uint8_t*)PY_mb_xian},
{"9426","xiao",(uint8_t*)PY_mb_xiao},
{"9464","xing",(uint8_t*)PY_mb_xing},
{"9826","xuan",(uint8_t*)PY_mb_xuan},
{"9264","yang",(uint8_t*)PY_mb_yang},
{"9464","ying",(uint8_t*)PY_mb_ying},
{"9664","yong",(uint8_t*)PY_mb_yong},
{"9826","yuan",(uint8_t*)PY_mb_yuan},
{"9264","zang",(uint8_t*)PY_mb_zang},
{"9364","zeng",(uint8_t*)PY_mb_zeng},
{"9424","zhai",(uint8_t*)PY_mb_zhai},
{"9426","zhan",(uint8_t*)PY_mb_zhan},
{"9426","zhao",(uint8_t*)PY_mb_zhao},
{"9436","zhen",(uint8_t*)PY_mb_zhen},
{"9468","zhou",(uint8_t*)PY_mb_zhou},
{"9482","zhua",(uint8_t*)PY_mb_zhua},
{"9484","zhui",(uint8_t*)PY_mb_zhui},
{"9486","zhun",(uint8_t*)PY_mb_zhun},
{"9486","zhuo",(uint8_t*)PY_mb_zhuo},
{"9664","zong",(uint8_t*)PY_mb_zong},
{"9826","zuan",(uint8_t*)PY_mb_zuan},
{"24264","chang",(uint8_t*)PY_mb_chang},
{"24364","cheng",(uint8_t*)PY_mb_cheng},
{"24664","chong",(uint8_t*)PY_mb_chong},
{"24826","chuan",(uint8_t*)PY_mb_chuan},
{"48264","guang",(uint8_t*)PY_mb_guang},
{"48264","huang",(uint8_t*)PY_mb_huang},
{"54264","jiang",(uint8_t*)PY_mb_jiang},
{"54664","jiong",(uint8_t*)PY_mb_jiong},
{"58264","kuang",(uint8_t*)PY_mb_kuang},
{"54264","liang",(uint8_t*)PY_mb_liang},
{"64264","niang",(uint8_t*)PY_mb_niang},
{"74264","qiang",(uint8_t*)PY_mb_qiang},
{"74664","qiong",(uint8_t*)PY_mb_qiong},
{"74264","shang ",(uint8_t*)PY_mb_shang},
{"74364","sheng",(uint8_t*)PY_mb_sheng},
{"74824","shuai",(uint8_t*)PY_mb_shuai},
{"74826","shuan",(uint8_t*)PY_mb_shuan},
{"94264","xiang",(uint8_t*)PY_mb_xiang},
{"94664","xiong",(uint8_t*)PY_mb_xiong},
{"94264","zhang",(uint8_t*)PY_mb_zhang},
{"94364","zheng",(uint8_t*)PY_mb_zheng},
{"94664","zhong",(uint8_t*)PY_mb_zhong},
{"94824","zhuai",(uint8_t*)PY_mb_zhuai},
{"94826","zhuan",(uint8_t*)PY_mb_zhuan},
{"248264","chuang",(uint8_t*)PY_mb_chuang},
{"748264","shuang",(uint8_t*)PY_mb_shuang},
{"948264","zhuang",(uint8_t*)PY_mb_zhuang},
};

#endif

