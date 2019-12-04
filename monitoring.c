int request_size_before;

void save_params_before(){
	
	request_size_before = web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT);
}


void save_params_after(char* url, char* transaction_name, char* label){
	
	lr_save_timestamp("timestamp", LAST );
	
	lr_save_int(web_get_int_property(HTTP_INFO_TOTAL_REQUEST_STAT)-request_size_before, "sentBytes");
		
	lr_save_int(web_get_int_property(HTTP_INFO_RETURN_CODE), "responseCode");
	
	lr_save_int(web_get_int_property(HTTP_INFO_DOWNLOAD_SIZE), "bytes");
	
	lr_save_int(web_get_int_property(HTTP_INFO_DOWNLOAD_TIME), "responseTime");
	
	lr_save_string("XDesc", "measurement");
	
	lr_save_string(label, "label");

	lr_save_string(url, "URL");
	
	lr_save_string(transaction_name, "transaction_name");
	
	if (atoi(lr_eval_string("{responseCode}")) < 400){
		lr_save_string("true", "success");
	} else 	lr_save_string("false", "success");
	
	lr_param_sprintf("result","%s,label=%s,responseCode=%s," 
	                 "success=%s,transaction_name=%s responseTime=%s000,bytes=%s,"
	 				 "sentBytes=%s,\URL=\"%s\",responseCodeValue=%s %s000000",
		   lr_eval_string("{measurement}"),
		   lr_eval_string("{label}"),
		   lr_eval_string("{responseCode}"),
		   lr_eval_string("{success}"),
		   lr_eval_string("{transaction_name}"),
		   lr_eval_string("{responseTime}"),
		   lr_eval_string("{bytes}"),
		   lr_eval_string("{sentBytes}"),
		   lr_eval_string("{URL}"),
		   lr_eval_string("{responseCode}"),
		   lr_eval_string("{timestamp}"));
	
	web_custom_request("TestRequest",
		"Method=POST",
		"URL=http://localhost:8086/write?db=db0",
		"Body={result}",
		LAST);
	
}