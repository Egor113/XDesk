UC01_Comment()
{
	int task_index;
	
	lr_think_time(THINKTIME);
	
	lr_start_transaction("UC03_TR02_Show_tasks");

	web_url("/api/task/countByState/", 
		"URL={Host}:{Port}/api/task/countByState/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		LAST);

	web_reg_save_param_json(
        "ParamName=taskIdS",
        "QueryString=$.content[*].id",
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
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		LAST);
	
	task_index = rand() % atoi(lr_eval_string("{taskIdS_count}")) + 1;
	
	lr_save_string(lr_paramarr_idx("taskIdS", task_index), "taskID");

	lr_end_transaction("UC03_TR02_Show_tasks",LR_AUTO);
	
	lr_think_time(THINKTIME);

	lr_start_transaction("UC03_TR03_Open_task");

	web_url("/api/task/{taskID}", 
		"URL={Host}:{Port}/api/task/{taskID}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/checkLogin", 
		"URL={Host}:{Port}/api/checkLogin", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		LAST);

	web_url("/api/ticket/{taskID}/comment/", 
		"URL={Host}:{Port}/api/ticket/{taskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR03_Open_task",LR_AUTO);

	lr_think_time(THINKTIME);

	lr_start_transaction("UC03_TR04_Add_comment");

	lr_end_transaction("UC03_TR04_Add_comment",LR_AUTO);

	lr_think_time(THINKTIME);

	lr_start_transaction("UC03_TR05_Submit_comment");

	lr_param_sprintf("url", "%s:%s/api/ticket/%s/comment/",
		   lr_eval_string("{Host}"),
		   lr_eval_string("{Port}"),
		   lr_eval_string("{taskID}"));
	
	save_params_before();
	
	web_custom_request("/api/ticket/{taskID}/comment/", 
		"URL={Host}:{Port}/api/ticket/{taskID}/comment/", 
		"Method=POST", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		"EncType=application/json; charset=utf-8", 
		"Body={\"text\":\"{Comment}\",\"files\":[]}", 
		LAST);
	
	save_params_after(lr_eval_string("{url}"),"UC03_TR05_Submit_comment","/api/ticket/{taskID}/comment/");

	web_url("/api/ticket/{taskID}/comment/", 
		"URL={Host}:{Port}/api/ticket/{taskID}/comment/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer={Host}:{Port}/", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_TR05_Submit_comment",LR_AUTO);

	lr_think_time(THINKTIME);
}
