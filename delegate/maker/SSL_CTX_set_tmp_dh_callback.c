int SUBST_SSL_CTX = 1;

#define SSL_CTRL_SET_TMP_DH_CB 4
void SSL_CTX_ctrl(int,int,int,void(*)());
void SSL_CTX_set_tmp_dh_callback(int ctx,void (*tmpdh_callback)())
{
	SSL_CTX_ctrl(ctx,SSL_CTRL_SET_TMP_DH_CB,0,tmpdh_callback);
}
