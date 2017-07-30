文件解释：

website: 网站所在
	index.html 为主页 单页网站
	pac-man-2724.jpg 为主页背景图
	Script.js 为d3js上Sunburst bilevel partition with tooltips（http://bl.ocks.org/vgrocha/1580af34e56ee6224d33）的数据可视化模版
	StyleSheet.css 为主页所用的级联样式表
	vgsales.json 为基于kaggle上Video Game Sales（https://www.kaggle.com/gregorut/videogamesales）处理后的数据文件

data: 原始数据与处理程序所在
	vgsales.csv 为原始数据文件，涵盖了16598个视频游戏的信息。
	csvTOjson.cpp 为将原始数据进行统计处理并改写成.json格式的程序代码


网站解释：

	目前已知只能使用Firefox浏览器打开（Chrome不支持Ajax本地访问，故无法打开数据文件vgsales.json，就无法加载数据可视化效果；IE也无法正常打开，原因未知）。
	打开网页后会提示使用Firefox浏览器打开，如果是Firefox浏览器则请点击确认；如果不是则请关闭页面，换成Firefox浏览器重新打开。
	因为数据量较大，需要耐心等待十几秒后页面才会加载完毕。
	可以看见页面中央有一个同心圆。
	第二圈上面显示的文字是视频游戏的各个分类，将鼠标在上面悬停可以看到分类的名字，分类字样，分类下所有游戏的总全球销量；第三个扇环上是各个游戏，将鼠标在上面悬停可以看到游戏名字，游戏的公司、平台和发售年份，游戏的全球销量。
	单击第二圈上的任意一个游戏种类，稍等片刻，可以放大看到这个种类的所有游戏，将鼠标在上面悬停可以看到游戏名字，游戏的公司、平台和发售年份，游戏的全球销量。单击中间的白色圆圈，稍等片刻，可以回到一开始能看到多种类的界面。
	每一个扇环的度数和其权重（即全球销量）成正比，可以可视化地看到各个游戏的销量情况与各个类型的总销量情况。