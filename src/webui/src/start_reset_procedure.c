
/*  Dowse - embedded WebUI based on Kore.io
 *
 *  (c) Copyright 2016 Dyne.org foundation, Amsterdam
 *  Written by Nicola Rossi <nicola@dyne.org>
 *
 * This source code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Public License as published
 * by the Free Software Foundation; either version 3 of the License,
 * or (at your option) any later version.
 *
 * This source code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * Please refer to the GNU Public License for more details.
 *
 * You should have received a copy of the GNU Public License along with
 * this source code; if not, write to:
 * Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */
#include <webui.h>

int start_reset_procedure(struct http_request * req) {
    template_t tmpl;
	attributes_set_t attr;
    char *html_rendered;
    struct kore_buf *out;
    int len;
    FILE *fp;
    out = kore_buf_alloc(0);
	attr=attrinit();

	/* Create reset file */
	fp=fopen(RESET_ADMIN_FILE,"w");
	if (fp==NULL) {
	    char m[1024];
	    snprintf(m,sizeof(m),"Error on creation of file [%s] [%s]", RESET_ADMIN_FILE , strerror(errno));
	    attributes_set_t att=attrinit();
	    webui_add_error_message(&att,m);
	    err(m);
	    return show_generic_message_page(req,att);
	}
	fclose(fp);

    /* Start a process to delete the file after 30seconds
     *      Note: the thread should listen SIGPOWER signal ? */
	pid_t child=fork();
	if (child==0) {
	    int i;
	    char m[1024];
	    for (i=30;i>0;i--) {
	        snprintf(m,sizeof(m)," Waiting other %d seconds",i);
	        kore_log(LOG_INFO,m);
	        func(m);
	        sleep(1);
	    }
	    unlink(RESET_ADMIN_FILE);
	    exit(0);
	}

	/* */
    WEBUI_DEBUG;

    template_load(asset_start_reset_procedure_html,asset_len_start_reset_procedure_html,&tmpl);
    template_apply(&tmpl,attr,out);

	/**/
    WEBUI_DEBUG;
    html_rendered = kore_buf_release(out, &len);
    http_response(req, 200, html_rendered, len);

    /**/
    WEBUI_DEBUG;
    kore_free(html_rendered);
	attrfree(attr);

    return (KORE_RESULT_OK);
}