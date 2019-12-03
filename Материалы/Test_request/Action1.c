//bool success;
//char measurement[1024];
//char label[1024];

Action1()
{

	web_reg_save_param("responseCode",
                 "LB=HTTP/1.1 ",
                 "RB= ",
				 LAST);
	
	web_reg_save_param("successStatus",
                 "LB=HTTP/1.1 ",
                 "RB= ",
				 LAST);
	
	web_url("/, 
		"URL=http://www.icicall.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		LAST);
	
	if (lr_eval_string("{c_buffer}") == "OK"){
		success = true;
	} else success = false;
	measurement = "loadrunner";
	measurement = "loadrunner";
	//	String result = measurement
//                + ",label=" + getLabel()
//                + ",responseCode=" + getResponseCode()
//                + ",success=" + getSuccess()
//                + " responseTime=" + getElapsed()
//                + ",bytes=" + getBytes()
//                + ",sentBytes=" + getSentBytes()
//                + ",URL=\"" + getURL()
//                + "\" " + getTimeStamp()
//                + timestamp0
//                + "\n";
//        
//	measurement - название вашей "таблицы", например, loadrunner
//	label - название запроса
//
// 	Итоговая строка выглядит как-то так:
// 	"loadrunner,label=/getMessage,responseCode=200
// 	,success=true responseTime=358,bytes=523133123
// 	,sentBytes=3234123,URL=\"http://azaza.com/getMessage\" 300012123123"

	
//
//	lr_param_sprintf("c_buffer", "%s{\"text\":\"%s\",\"header\":\"%s\"," 
//		                 "\"ticketStateId\": 0,\"serviceId\": \"%s\"," 
//		                 "\"files\": [],\"inventoryNumberId\": \"%s\"," 
//		                 "\"shopId\": \"%s\"}",
//		   lr_eval_string("{c_buffer}"),
//		   lr_eval_string("{Text}"),
//		   lr_paramarr_idx("serviceNames", j),
//		   lr_eval_string("{serviceId}"),
//		   //lr_eval_string("{FileID}"),
//		   lr_eval_string("{inventoryNumberId}"),
//		   lr_eval_string("{shopID}"));

	return 0;
}