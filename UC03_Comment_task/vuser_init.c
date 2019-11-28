int rc = 0;
char *VtsServer = "localhost";
int nPort = 8888;

PVCI2 pvci = 0;
	
	
vuser_init()
{
	pvci = lrvtc_connect(VtsServer, nPort, VTOPT_KEEP_ALIVE);
	lr_log_message("pvci=%d\n", pvci);
	
	return 0;
}
