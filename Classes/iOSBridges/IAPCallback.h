//
//  IAPCallback.h
//  NabuzaI
//
//  Created by Lee Samgu on 8/21/13.
//
//

#ifndef __NabuzaI__IAPCallback__
#define __NabuzaI__IAPCallback__

#include "cocos2d.h"

using namespace cocos2d;

namespace iOSBridge
{
	namespace Callbacks
	{
		struct IAPItem
		{
			std::string identification;
			std::string name;
			std::string localizedTitle;
			std::string localizedDescription;
			float price;
		};
        
		class IAPCallback
		{
		public:
			virtual void productsDownloaded(CCArray *products);
		};
	}
}

#endif /* defined(__NabuzaI__IAPCallback__) */
