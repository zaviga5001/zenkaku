#include "MyStr.h"

std::vector< std::string > CMyStr::separate(std::string inStr)
{
	std::vector< std::string > sList;	/* 1文字ずつ分けた結果を保持 */
	int count = 0;		/* 全角文字を読み込み始めてから何回たったか */ 
	char bufC[10];		/* 全角文字保存用 */
	bool isLastFULL = false;	/* 前回が全角かどうか */

	// clear list
	sList.clear();

	for(int i=0;i < inStr.length(); i++)
	{
		// 今回が半角
		if(inStr.at(i) > 0)
		{
			// 前回が全角
			if(isLastFULL)
			{
				bufC[count] = '\0';
				sList.push_back( mystd::to_string(bufC) );
			}

			// リストに追加
			sList.push_back( mystd::to_string(inStr.at(i)) );

			isLastFULL = false;
			count = 0;
		}

		// 今回が半角
		else
		{
			if(count == 3)
			{
				bufC[count] = '\0';
				sList.push_back( mystd::to_string(bufC) );
				count = 0;
			}

			isLastFULL = true;
			bufC[count++] = inStr.at(i);
		}
	}

	// 最後の文字が全角だったときの処理
	if(isLastFULL)
	{
		bufC[count] = '\0';
		sList.push_back( mystd::to_string(bufC) );
	}

	return sList;
}

int CMyStr::length(std::string tmpstr)
{
	std::vector< std::string > sList;	/* 1文字ずつ分けた結果を保持 */
	sList = separate(tmpstr);

	return(sList.size());
}

int CMyStr::capacity(std::string tmpstr)
{
	return(tmpstr.capacity());
}

std::string CMyStr::substr(std::string tmpstr, int start)
{
	std::vector< std::string > sList;	/* 1文字ずつ分けた結果を保持 */
	sList = separate(tmpstr);
	std::string retbuf;

	for (int i = start; i < sList.size(); i++)
	{
		retbuf += sList[i];
	}

	return(retbuf);
}

std::string CMyStr::substr(std::string tmpstr, int start, int len)
{
	std::vector< std::string > sList;	/* 1文字ずつ分けた結果を保持 */
	sList = separate(tmpstr);
	std::string retbuf;

	for (int i = start; i < sList.size() && i < start + len; i++)
	{
		retbuf += sList[i];
	}

	return(retbuf);
}

