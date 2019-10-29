<?php
class Struct{
	public $length;
	public function __construct($array){
		$this->length = count($array);
	}

	/**
	*	冒泡排序  O(n*n)  稳定排序 原地排序
	*/
	public function bubbleSort($data = array()){
		if($this->length <= 1) return false;

		for($i = 1; $i <= $this->length; $i++){
			$flag = fasle;
			for($j = 0; $j < $this->length - $i ;$j++){
				if($data[$j] > $data[$j+1]){
					$tmp = $data[$j];
					$data[$j] = $data[$j+1];
					$data[$j+1] = $tmp;
					$flag = true;
				}
			}

			if(!$flag) break;
		}

		return $data;
	}

	/**
	*	插入排序  O(n*n)  稳定排序 原地排序  最好时间复杂度 O(n)
	*/
	public function insertSort($data = array()){
		/*通常的做法就是将第一个元素看做是有序的元素（即待排序列的第一个元素看做是有序序列），然后我们将第二个元素和有序序列（即第一个元素）作比较，按正确的序列插入到序列中去。然后再将第三个元素和前面有序序列（即整个待排序列的前两个元素）作比较，将第三个插入到前两个元素中去，使得前三个元素有序。以此类推，直到所有的元素都有序。*/
		if($this->length <= 1) return false;

		for($i = 1; $i < $this->length; ++$i){
			$value = $data[$i];
			for($j = $i - 1;$j >= 0; --$j){
				if($data[$j] > $value){
					$data[$j+1] = $data[$j];
				}else{
					break;
				}
			}
			$data[$j+1] = $value;
		}

		return $data;
	}	

	/**
	*	选择排序  O(n*n)  非稳定排序 原地排序  空间复杂度O(1)  最好/最坏/平均时间复杂度 O(n*n)
	*   https://www.cnblogs.com/wgq123/p/6543698.html
	*   原理： 在一列数字中,选出最小数与第一个位置的数交换。然后在剩下的数当中再找最小的与第二个位置的数交换,如此循环到倒数第二个数和最后一个数比较为止。(以下都是升序排列，即从小到大排列)
	*/
	public function selectSort($data = array()){
		$count = count($data);

		for($i = 0; $i < $count - 1; $i++){
			//定义最小位置
			$minAddr = $i;
			for($j = $i + 1; $j < $count; $j++){
				if($data[$j] < $data[$minAddr]){
					$minAddr = $j;
				}
			}

			$tmp = $data[$i];
			$data[$i] = $data[$minAddr];
			$data[$minAddr] = $tmp;
		}

		return $data;
	}

	/**
	*	快速排序  O(nlogn)  非稳定排序 原地排序
	*	https://blog.csdn.net/qq_25221835/article/details/80847722
	*/
	public function quickSort($left, $right, &$data){
		if($left > $right) return;
		$i = $left;
		$j = $right;
		$tmp = $data[$left];
		
		while($i < $j){
			//顺序很重要，要先从右边开始找 
			while ($data[$j] >= $tmp && $i < $j) {
				$j--;
			}

			while ($data[$i] <= $tmp && $i < $j) {
				$i++;
			}
			
			//交换两个数在数组中的位置
			if($i < $j){
				$temp = $data[$i];
				$data[$i] = $data[$j];
				$data[$j] = $temp;
			}
		}
		
		//最终将基准数归位
		$data[$left] = $data[$i];
		$data[$i] = $tmp;
		
		//处理左边数据
		quickSort(0,$i-1,$data);
		//处理右边数据
		quickSort($i+1,$right,$data);
	}

	/**
	*	归并排序 O(nlogn)  稳定排序 非原地排序
	*	https://www.jb51.net/article/95016.htm
	*/
	public function mergeSort(&$data){
		$count = count($data);
		$this->getMergeSortResult($data,0,$count-1);
	}

	public function getMergeSortResult(&$data,$left,$right){
		if($left < $right){
			$center = floor(($left+$right)/2);
			$this->getMergeSortResult($data,$left,$center);
			$this->getMergeSortResult($data,$center+1,$right);

			//合并
			while ($left <= $center && $center+1 <= $right) {
				# code...
			}
		}

		echo '<pre>';
		print_r($data);
	}

	/*
	*	计数排序  O(n+k)[k是数据范围]  稳定排序 非原地排序
	*/
	public function countSort($data = array()){
		$max = max($data);
		for($i = 0; $i <= $max; $i++){
			$tmp[$i] = 0;
		}

		//计算每个桶内元素的个数
		for($i = 0; $i < $this->length; $i++){
			$tmp[$data[$i]]++;
		}

		//依次累加
		for($i = 1; $i <= $max; $i++){
			$tmp[$i] = $tmp[$i] + $tmp[$i-1];
		}

		$tmps = [];
		//从后向前扫描数组
		for($i = $this->length - 1; $i >= 0; $i--){
			// $index = $tmp[$data[$i]] - 1;
			// $tmps[$index] = $data[$i];
			$tmps[$tmp[$data[$i]] - 1] = $data[$i];
			$tmp[$data[$i]]--;
		}

		for($i = 0; $i < $this->length; $i++){
			$data[$i] = $tmps[$i];
		}
		unset($tmps);
		return $data;
	}

	/**
	*	桶排序 O(n)[k是数据范围]  稳定排序 非原地排序
	*/
	public function bucketSort($data){
		$min = min($data);
		$max = max($data);
		
		$bucket = array_fill($min,$max-$min+1,0);
		
		
		//数据入桶
		foreach($data as $key=>$val){
			$bucket[$val]++; //对应桶的个数计增
		}

		$sort = [];
		//数据出桶
		foreach($bucket as $k => $v){
			for($i = 1;$i <= $v; $i++){
				$sort[] = $k;
			}
		}

		return $sort;
	}

	/*
	*	基数排序 O(dn)[d是数据维度]  稳定排序 非原地排序
	*/
	public function baseSort(array &$data,$loop){
		/*
		 *	基数排序(Radix Sort)是桶排序的扩展，它的基本思想是：将整数按位数切割成不同的数字，然后按每个位数分别比较。
	     *  具体做法是：将所有待比较数值统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排
	     *序。这样从最低位排序一直到最高位排序完成以后, 数列就变成一个有序序列。
		*/

		$tmp = [];
		for($i = 0; $i < 10; $i++){
			$tmp[$i] = [];
		}

		$arrayNum = count($data);
		$tempNum = (int)pow(10,$loop-1);
		 
		for($i = 0; $i < $arrayNum; $i++){
			$yu = ($data[$i] / $tempNum) % 10;
			array_push($tmp[$yu],$data[$i]);
		}

		$k = 0;
		for($i = 0; $i < 10; $i++){
			//出桶
			while(count($tmp[$i]) > 0){
				$data[$k++] = array_shift($tmp[$i]);
			}
		}
	}

	//获取基数排序结果
	public function getBaseSortResult(array &$data){
		$max = max($data);
		$count = 1;
		$tmp = floor($max/10);
		while ($tmp != 0) {
			$count++;
			$tmp = floor($tmp/10);
		}

		for($i = 1;$i <= $count; $i++){
			$this->baseSort($data,$i);
		}
	}

	/**
	*	简单二分查找  二分查找针对的是一个有序的数据集合  O(logn)
	*   1.二分查找依赖顺序结构(数组),针对有序数据; 
	*	2.数据量太小/太大不适合二分查找; 
	*	3.凡是用二分查找能解决的,绝大部分更倾向于用散列表或者二叉查找树;
	*/
	public function easyErfenSort($data = array(), $key= 0){
		/**
		*	二分查找针对的是一个有序的数据集合，查找思想有点类似分治思想。每次都通过跟区间的中间元素对比，将待查找的区间缩小为之前的一半，直到找到要查找的元素，或者区间被缩小为 0
		*/
		$low = 0;
		$high = $this->length - 1;

		while ($low <= $high) {
			// $middle = $low + (($high - $low)/2);
			$middle = $low + (($high - $low) >> 1);
			$middle = (int)$middle;
			if($key == $data[$middle]){
				return $middle;
			}elseif($key < $data[$middle]) {
				$high = $middle - 1;
			}else{
				$low = $middle + 1;
			}
		}

		return -1;
	}

	/**
	*	变体二分查找  【查找第一个值等于给定值的元素】&& 【查找最后一个值等于给定值的元素】
	*/
	public function firstEqualErfenSort($data = array(), $key = 0){
		$low = 0;
		$high = $this->length - 1;
		while ($low <= $high) {
			$middle = $low + ($high - $low)/2;
			$middle = (int)$middle;
			if($key < $data[$middle]){
				$high = $middle - 1;
			}else if($key > $data[$middle]){
				$low = $middle + 1;
			}else{
				//【查找第一个值等于给定值的元素】
				// if($middle == 0 || $data[$middle - 1] != $key){
				// 	return $middle;
				// }else{
				// 	$high = $middle - 1;
				// }

				//【查找最后一个值等于给定值的元素】
				if($middle == 0 || $data[$middle + 1] != $key){
					return $middle;
				}else{
					$low = $middle + 1;
				}
			}
		}

		return -1;
	}

	/**
	*	变体二分查找  【查找第一个大于等于给定值的元素】&&【查找最后一个小于等于给定值的元素】
	*/
	public function firstBigOrLittleKeySort($data = array(), $key = 0){
		$low = 0;
		$high = $this->length - 1;
		while ($low <= $high) {
			$middle = $low + (($high - $low) >> 1);
			//【查找第一个大于等于给定值的元素】
			// if( $data[$middle] >= $key ){
			// 	if($middle == 0 || $data[$middle - 1] < $key){
			// 		return $middle;
			// 	}else{
			// 		$high = $middle - 1;
			// 	}
			// }else{
			// 	$low = $middle + 1;
			// }

			//【查找第一个小于等于给定值的元素】
			if( $data[$middle] <= $key ){
				if($middle == $high || $data[$middle + 1] > $key){
					return $middle;
				}else{
					$low = $low + 1;
				}
			}else{
				$high = $middle - 1;
			}
		}

		return -1;
	}

	/**
	*	跳表    
	*	1.Redis 中的有序集合（Sorted Set）就是用跳表来实现
	*/

	/**
	*	散列表    
	*	1.开放寻址法的核心思想是,如果出现了散列冲突,我们就重新探测一个空闲位置,将其插入;
	*	  用装载因子（load factor）来表示空位的多少,
	*			【散列表的装载因子 = 填入表中的元素个数 / 散列表的长度】
	*	  装载因子越大，说明空闲位置越少，冲突越多，散列表的性能会下降;
	*/
	public function hashTable(){
		//hash("nice")=(("n" - "a") * 26*26*26 + ("i" - "a")*26*26 + ("c" - "a")*26+ ("e"-"a")) / 78978
	}
}


$array = [43, 343, 342, 1, 128, 2, 4249, 814, 687, 654, 3];
$array = [4,2,6,8,10,11];
$struct = new Struct($array);
// $result = $struct->bubbleSort($array);
// $result = $struct->countSort($array);
// $result = $struct->insertSort($array);
// $result = $struct->quickSort($array);
// $result = $struct->quickSort(0,10,$array);
// echo '<pre>';
// var_dump($array);die;
// $result = $struct->easyErfenSort($array,99);
// $result = $struct->firstBigOrLittleKeySort($array,5);
// $result = $struct->createData();
// $struct->getBaseSortResult($array);
$result = $struct->bucketSort($array);
echo '<pre>';
var_dump($result);die;
// $result = $struct->selectSort($array);

function mergeSort($data){
	$len=count($data);
    if($len <= 1){
        return $data;
    }

	$m = floor(count($data)/2);
	$left = array_splice($data,0,$m);
	$right = $data;

	$leftarr = mergeSort($left);
	$rightarr = mergeSort($right); 

	$data = mergeArray($leftarr,$rightarr);

	return $data;
}

function mergeArray($arr1,$arr2){
	$i = $j = 0;
	$length1 = count($arr1);
	$length2 = count($arr2);
	while(count($arr1) && count($arr2)){
		
		// $tmp[] = $arr1[$i] < $arr2[$j] ? $arr1[$i++] : $arr2[$j++];
		$tmp[] = $arr1[$i] < $arr2[$j] ? array_shift($arr1) : array_shift($arr2);
	}

	return array_merge($tmp,$arr1,$arr2);
	// while ($i < $length1) {
	// 	$tmp[] = $arr1[$i++];
	// }

	// while ($j < $length2) {
	// 	$tmp[] = $arr2[$j++];
	// }

	// return $tmp;
}
// $result = mergeArray($arr1,$arr2);
// $struct->mergeSort($array);


// $result = $struct->baseSort($array,1);
// echo '<pre>';
// var_dump($a);

//安装性能分析工具php  Xhprof  https://blog.csdn.net/u011142688/article/details/78477395
//https://blog.csdn.net/qq_28602957/article/details/72697901

$arr = [28, 22];
for ($i = 0; $i < 98; $i++) {
    array_push($arr, rand(0, 1000));
}

// $result = mergeSort($arr);

function getHe50($arr){
	$low = 0;
	$high = count($arr) - 1;
	while($low < $high){
		$tmp = $arr[$low] + $arr[$high];
		if($tmp == 50){
			return $arr[$low] .'+'. $arr[$high] .'=50'; 
		}elseif($tmp < 50){
			$low++;
		}else{
			$high--;
		}
	}
}

$result = getHe50($result);
// echo $result;
// echo '<pre>';
// var_dump($result);
$result = pack('H*', "bcb04b7e103a0cd8b54763051cef08bc55abe029fdebae5e1d417e2ffb2a00a3");
echo $result;





