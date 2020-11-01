# 内容

桌子上有一只盘子，最多可容纳两个水果，每次只能放入或取出一个水果。爸爸专向
盘子放苹果（apple），妈妈专向盘子中放桔子（orange）；儿子专等吃盘子中的桔
子，女儿专等吃盘子中的苹果。请用P、V操作来实现爸爸、妈妈、儿子、女儿之间的
同步与互斥关系。 

# 试验

开始时，运行init之后先运行 father，father 放了两个苹果就 sleep 了

![image-20201101135650312](../images/image-20201101135650312.png)

然后再运行 son，由于没有 orange， 所以 son 在 sleep

![image-20201101135756114](../images/image-20201101135756114.png)

然后运行 mother ，mother 取了 orange 发现放不进篮子， 就 sleep 了

![image-20201101135915135](../images/image-20201101135915135.png)

接着运行 daughter 

![image-20201101140036402](../images/image-20201101140036402.png)

出现异常：儿子自从运行后就再也没 sleep；

debug：儿子拿完orange后应该v(empty), 而不应该v(orange)

![image-20201101140216882](../images/image-20201101140216882.png)

修改之后再运行，先初始化每一个终端

![image-20201101141850974](../images/image-20201101141850974.png)

运行father

![image-20201101141931368](../images/image-20201101141931368.png)

运行son



![image-20201101141953408](../images/image-20201101141953408.png)

运行mother

![image-20201101142109032](../images/image-20201101142109032.png)



![image-20201101142150453](../images/image-20201101142150453.png)



得到了正常的运行状态。