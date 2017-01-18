#include <kore.h>
#include <http.h>
#include <time.h>
#include <attributes_set.h>



/********/
#define FREDD_DEVELOP

#ifdef FREDD_DEVELOP
#define template_load(a,size,ptr_template) find_nearest_asset_and_load_template(#a,size,ptr_template)
#else
/* In static compiling we use the static templating */
#define template_load _internal_static_template_load
#endif


/***/

#ifndef _WEBUI_DEBUG_H
#define _WEBUI_DEBUG_H
#ifndef __where_i_am__
static uint8_t __buf_where_i_am__[256];

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define __where_i_am__ __FILE__ ":" TOSTRING(__LINE__)

#endif


#define __WEBUI_DEBUG__
#ifndef __WEBUI_DEBUG__
#define WEBUI_DEBUG {}
#else
#define WEBUI_DEBUG {func("WEBUI_DEBUG: %ld : %s:%d",time(NULL),__FILE__,__LINE__);}
#endif

/* Define mapping with bootstap alert level */
#define WEBUI_level_error (char*)"danger"
#define WEBUI_level_warning (char*)"warning"
#define WEBUI_level_info (char*)"info"
#define WEBUI_level_success (char*)"success"

/* Definition of function and prototype for add message to TMPL_LOOP */
void _webui_add_message_level(attributes_set_t *ptr_attrl,const char*level,const char *log_message);

#define WEBUI_DEF_ERROR_LEVEL_MESSAGE_PROTOTYPE(LEVEL) \
    void webui_add_ ## LEVEL ## _message  (attributes_set_t *ptr_attrl,const char *log_message) ;

WEBUI_DEF_ERROR_LEVEL_MESSAGE_PROTOTYPE(info) ;
WEBUI_DEF_ERROR_LEVEL_MESSAGE_PROTOTYPE(warning) ;
WEBUI_DEF_ERROR_LEVEL_MESSAGE_PROTOTYPE(success) ;
WEBUI_DEF_ERROR_LEVEL_MESSAGE_PROTOTYPE(error);


#define WEBUI_DEF_ERROR_LEVEL_MESSAGE(LEVEL) \
        void webui_add_ ## LEVEL ## _message (attributes_set_t *ptr_attrl,const char *log_message) \
            { _webui_add_message_level(ptr_attrl, WEBUI_level_ ##LEVEL ,log_message); }
/**/

#define TMPL_VAR_LEVEL_MESSAGE "level"
#define TMPL_VAR_TEXT_MESSAGE "text"

#define TMPL_VAR_MESSAGE_LOOP "message_loop"

/* TODO aggiungere stacktrace debug */
#endif
