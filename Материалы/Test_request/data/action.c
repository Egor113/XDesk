Action()
{

	web_add_cookie("ui_language=en; DOMAIN=www.icicall.ru");

	web_url("www.icicall.ru", 
		"URL=http://www.icicall.ru/", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/images/body-tail.gif", ENDITEM, 
		"Url=/images/logos/icicall-en.png", ENDITEM, 
		"Url=/i18n/dictionary.json", ENDITEM, 
		"Url=/images/top-tail.gif", ENDITEM, 
		"Url=/images/tail-bot.gif", ENDITEM, 
		"Url=/images/top-index-bg.jpg", ENDITEM, 
		"Url=/images/menu-act.gif", ENDITEM, 
		"Url=/images/box-tail.jpg", ENDITEM, 
		"Url=/images/box-top.jpg", ENDITEM, 
		"Url=/images/line-ver.gif", ENDITEM, 
		"Url=/images/info-box1.jpg", ENDITEM, 
		"Url=/images/box-bot.jpg", ENDITEM, 
		"Url=/images/link-right1.gif", ENDITEM, 
		"Url=/images/link-left1.gif", ENDITEM, 
		"Url=/images/link-tail1.gif", ENDITEM, 
		"Url=/images/info-box2.jpg", ENDITEM, 
		"Url=/images/info-box3.jpg", ENDITEM, 
		"Url=/images/footer-divider.gif", ENDITEM, 
		"Url=/images/ideal-bubble.png", ENDITEM, 
		"Url=/i18n/news.json", ENDITEM, 
		"Url=/images/footer.gif", ENDITEM, 
		"Url=/favicon.ico", "Referer=", ENDITEM, 
		LAST);

	return 0;
}