UC03_Logout()
{
	lr_start_transaction("UC03_TR06_Logout");

	web_url("/api/logout", 
		"URL={Host}:{Port}/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/login", 
		"URL={Host}:{Port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t20.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR06_Logout",LR_AUTO);
	
	return 0;
}
