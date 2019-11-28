int task_index;

Action()
{

	web_url("/", 
		"URL={Host}:{Port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t29.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/login", 
		"URL={Host}:{Port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t30.inf", 
		"Mode=HTML", 
		LAST);

	lr_start_transaction("UC04_TR01_Login");

	web_submit_data("/api/login", 
		"Action={Host}:{Port}/api/login", 
		"Method=POST", 
		"TargetFrame=", 
		"Referer={Host}:{Port}/login", 
		"Snapshot=t31.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=login", "Value={Login}", ENDITEM, 
		"Name=password", "Value={Password}", ENDITEM, 
		"Name=rememberMe", "Value=false", ENDITEM, 
		LAST);

	web_url("/", 
		"URL={Host}:{Port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/login", 
		"Snapshot=t32.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL={Host}:{Port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t33.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL={Host}:{Port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t34.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL={Host}:{Port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t35.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL={Host}:{Port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t36.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/ticket/", 
		"URL={Host}:{Port}/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t37.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	web_set_sockets_option("SSL_VERSION", "TLS1.2");

	lr_end_transaction("UC04_TR01_Login",LR_AUTO);

	lr_start_transaction("UC04_TR02_Tasks");

	web_url("/api/task/countByState/", 
		"URL={Host}:{Port}/api/task/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		LAST);
	
	web_reg_save_param_json(
        "ParamName=taskIdS",
        "QueryString=$.content[?(@.stateId = 1)].id",
        "SelectALL=Yes",
        SEARCH_FILTERS,
        "Scope=Body",
        "LAST");
	
	web_custom_request("/api/task/", 
		"URL={Host}:{Port}/api/task/?state=1&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	task_index = rand() % atoi(lr_eval_string("{taskIdS_count}")) + 1;
	
	lr_save_string(lr_paramarr_idx("taskIdS", task_index), "taskID");
	
	lr_end_transaction("UC04_TR02_Tasks",LR_AUTO);

	lr_start_transaction("UC04_TR03_Choose_task");

	web_url("{/api/task/{taskID}}", 
		"URL={Host}:{Port}/api/task/{taskID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t41.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL={Host}:{Port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t42.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/{taskID}/comment/", 
		"URL={Host}:{Port}/api/ticket/{taskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t43.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC04_TR03_Choose_task",LR_AUTO);

	lr_start_transaction("UC04_TR04_To_Incident");

	web_custom_request("/api/ticket/{taskID}", 
		"URL={Host}:{Port}/api/ticket/{taskID}", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t44.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/{taskID}/comment/", 
		"URL={Host}:{Port}/api/ticket/{taskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t45.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC04_TR04_To_Incident",LR_AUTO);

	lr_think_time(39);

	lr_start_transaction("UC04_TR05_Close_Incident");

	web_custom_request("/api/ticket/{taskID}/solve/", 
		"URL={Host}:{Port}/api/ticket/{taskID}/solve/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t46.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_url("/", 
		"URL={Host}:{Port}/", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t47.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL={Host}:{Port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t48.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/user/info", 
		"URL={Host}:{Port}/api/user/info", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t49.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/4", 
		"URL={Host}:{Port}/api/ticket/countByState/4", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t50.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/countByState/", 
		"URL={Host}:{Port}/api/ticket/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t51.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/task/countByState/", 
		"URL={Host}:{Port}/api/task/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t52.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("/api/task/", 
		"URL={Host}:{Port}/api/task/?state=1&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t53.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	web_custom_request("/api/ticket/", 
		"URL={Host}:{Port}/api/ticket/?state=-1,0,1,5&page=0&size=10", 
		"Method=GET", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t54.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);

	lr_end_transaction("UC04_TR05_Close_Incident",LR_AUTO);

	lr_think_time(91);

	lr_start_transaction("UC04_TR06_Logout");

	web_url("/api/logout", 
		"URL={Host}:{Port}/api/logout", 
		"TargetFrame=", 
		"Resource=0", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t55.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/login", 
		"URL={Host}:{Port}/login", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t56.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC04_TR06_Logout",LR_AUTO);

	return 0;
}