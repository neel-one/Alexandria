//
//  error.h
//  alexandria
//
//  Created by Neel Shah on 3/7/20.
//  Copyright © 2020 Neel Shah. All rights reserved.
//

#ifndef error_h
#define error_h

#include <exception>

class OperationError: public std::exception {};
class NotImplementedError: public std::exception {};


#endif /* error_h */
