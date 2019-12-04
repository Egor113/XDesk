UC01_Logout()
{
	lr_start_transaction("UC01_TR04_Logout");

	web_url("/api/logout", 
		"URL={Host}:{Port}/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t31.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/login", 
		"URL={Host}:{Port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t32.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC01_TR04_Logout",LR_AUTO);
	
	return 0;
}
