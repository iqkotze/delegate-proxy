/// RC4 for the PDF filter; OpenSSL 3 offers RC4 only in the legacy provider.
#define RC4_INT unsigned int
typedef struct {
	RC4_INT x,y;
	RC4_INT data[256];
} RC4_KEY;

void myRC4_set_key(RC4_KEY *key,int len,const unsigned char *data){
	RC4_INT *d = key->data;
	RC4_INT i,j = 0,t;
	int k = 0;

	for( i = 0; i < 256; i++ )
		d[i] = i;
	key->x = 0;
	key->y = 0;
	if( len <= 0 )
		return;
	for( i = 0; i < 256; i++ ){
		t = d[i];
		j = (j + t + data[k]) & 0xFF;
		d[i] = d[j];
		d[j] = t;
		if( ++k == len )
			k = 0;
	}
}

void myRC4(RC4_KEY *key,unsigned long len,const unsigned char *in,unsigned char *out){
	RC4_INT *d = key->data;
	RC4_INT x = key->x,y = key->y,tx,ty;
	unsigned long i;

	for( i = 0; i < len; i++ ){
		x = (x + 1) & 0xFF;
		tx = d[x];
		y = (y + tx) & 0xFF;
		ty = d[y];
		d[x] = ty;
		d[y] = tx;
		out[i] = in[i] ^ d[(tx + ty) & 0xFF];
	}
	key->x = x;
	key->y = y;
}
