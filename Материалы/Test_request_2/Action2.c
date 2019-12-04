Action2()
{

	int request_size_before = 0;
	
	web_reg_save_param_regexp("ParamName=successStatus",
        "RegExp=OK",
        "Group=0",
        "Notfound=warning",
        LAST);
	
	web_save_header(REQUEST,"request_header");
	
	request_size_before = web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT);
	
	web_url("/", 
		"URL=http://www.icicall.ru/ideal.html", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);
	
	lr_save_timestamp("timestamp", LAST );
	
	lr_save_int(web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT)-request_size_before, "sentBytes");
		
	lr_save_int(web_get_int_property(HTTP_INFO_RETURN_CODE), "responseCode");
	
	lr_save_int(web_get_int_property(HTTP_INFO_DOWNLOAD_SIZE), "bytes");
	
	lr_save_int(web_get_int_property(HTTP_INFO_DOWNLOAD_TIME), "responseTime");
	
	lr_save_string("loadrunner", "measurement");
	
	lr_save_string("/", "label");
	
	lr_save_string("\"http://www.icicall.ru/ideal.html\"", "URL");
	
	if (strcmp(lr_eval_string("{successStatus}"), "OK") == 0){
		lr_save_string("true", "success");
	} else 	lr_save_string("false", "success");
	
	lr_param_sprintf("result","%s,label=%s,responseCode=%s," 
	                 "success=%s responseTime=%s000,bytes=%s,"
	 				 "sentBytes=%s,URL=%s %s000000",
		   lr_eval_string("{measurement}"),
		   lr_eval_string("{label}"),
		   lr_eval_string("{responseCode}"),
		   lr_eval_string("{success}"),
		   lr_eval_string("{responseTime}"),
		   lr_eval_string("{bytes}"),
		   lr_eval_string("{sentBytes}"),
		   lr_eval_string("{URL}"),
		   lr_eval_string("{timestamp}"));
	
	web_custom_request("TestRequest",
		"Method=POST",
		"URL=http://localhost:8086/write?db=db0",
		"Body={result}",
		LAST);
		
	return 0;
}
