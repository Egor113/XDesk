UC01_Logout()
{
	lr_start_transaction("UC04_TR06_Logout");

	web_url("/api/logout", 
		"URL={Host}:{Port}/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t55.inf", 
		"Mode=HTML", 
		LAST);

	lr_param_sprintf("url", "%s:%s/api/login",
		   lr_eval_string("{Host}"),
		   lr_eval_string("{Port}"));
	
	save_params_before();
	
	web_url("/login", 
		"URL={Host}:{Port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t56.inf", 
		"Mode=HTML", 
		LAST);

	save_params_after(lr_eval_string("{url}"),"UC04_TR06_Logout","/login");
	
	lr_end_transaction("UC04_TR06_Logout",LR_AUTO);
	
	return 0;
}
