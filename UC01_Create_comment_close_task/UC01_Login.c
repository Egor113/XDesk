UC01_Login()
{
	web_url("/", 
		"URL={Host}:{Port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/login", 
		"URL={Host}:{Port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_start_transaction("UC01_TR01_Login");

	lr_param_sprintf("url", "%s:%s/api/login",
		   lr_eval_string("{Host}"),
		   lr_eval_string("{Port}"));
	
	save_params_before();
	
	web_submit_data("/api/login", 
		"Action={Host}:{Port}/api/login", 
		"Method=POST", 
		"TargetFrame=", 
		"Referer={Host}:{Port}/login", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=login", "Value={Login}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=rememberMe", "Value=false", ENDITEM, 
		LAST);
	
	save_params_after(lr_eval_string("{url}"),"UC01_TR01_Login","/api/login");

	web_url("/", 
		"URL={Host}:{Port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/login", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL={Host}:{Port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL={Host}:{Port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL={Host}:{Port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL={Host}:{Port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/ticket/", 
		"URL={Host}:{Port}/api/ticket/?state=-1,0,1,5&page=0" 
		"&size=10",
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC01_TR01_Login",LR_AUTO);
	
	return 0;
}
