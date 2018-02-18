/* ES40 emulator.
 * Copyright (C) 2007-2008 by the ES40 Emulator Project
 *
 * WWW    : http://www.es40.org
 * E-mail : camiel@es40.org
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * 
 * Although this is not required, the author would appreciate being notified of, 
 * and receiving any modifications you may make to the source code that might serve
 * the general public.
 *
 * Parts of this file based upon the Poco C++ Libraries, which is Copyright (C) 
 * 2004-2006, Applied Informatics Software Engineering GmbH. and Contributors.
 */

/**
 * $Id: Exception.cpp,v 1.1 2008/05/31 15:47:22 iamcamiel Exp $
 *
 * X-1.1        Camiel Vanderhoeven                             31-MAY-2008
 *      Initial version for ES40 emulator.
 **/

//
// Exception.cpp
//
// $Id: Exception.cpp,v 1.1 2008/05/31 15:47:22 iamcamiel Exp $
//
// Library: Foundation
// Package: Core
// Module:  Exception
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//

#include "Exception.h"
#include <typeinfo>

CException::CException(int code): _pNested(0), _code(code)
{
}


CException::CException(const std::string& msg, int code): _msg(msg), _pNested(0), _code(code)
{
}


CException::CException(const std::string& msg, const std::string& arg, int code): _msg(msg), _pNested(0), _code(code)
{
	if (!arg.empty())
	{
		_msg.append(": ");
		_msg.append(arg);
	}
}


CException::CException(const std::string& msg, const CException& nested, int code): _msg(msg), _pNested(nested.clone()), _code(code)
{
}


CException::CException(const CException& exc):
	std::exception(exc),
	_msg(exc._msg),
	_code(exc._code)
{
	_pNested = exc._pNested ? exc._pNested->clone() : 0;
}

	
CException::~CException() throw()
{
	delete _pNested;
}


CException& CException::operator = (const CException& exc)
{
	if (&exc != this)
	{
		delete _pNested;
		_msg     = exc._msg;
		_pNested = exc._pNested ? exc._pNested->clone() : 0;
		_code    = exc._code;
	}
	return *this;
}


const char* CException::name() const throw()
{
	return "Exception";
}


const char* CException::className() const throw()
{
	return typeid(*this).name();
}

	
const char* CException::what() const throw()
{
	return name();
}

	
std::string CException::displayText() const
{
	std::string txt = name();
	if (!_msg.empty())
	{
		txt.append(": ");
		txt.append(_msg);
	}
	return txt;
}


CException* CException::clone() const
{
	return new CException(*this);
}


void CException::rethrow() const
{
	throw *this;
}


POCO_IMPLEMENT_EXCEPTION(CLogicException, CException, "Logic exception")
POCO_IMPLEMENT_EXCEPTION(CAssertionViolationException, CLogicException, "Assertion violation")
POCO_IMPLEMENT_EXCEPTION(CNullPointerException, CLogicException, "Null pointer")
POCO_IMPLEMENT_EXCEPTION(CBugcheckException, CLogicException, "Bugcheck")
POCO_IMPLEMENT_EXCEPTION(CInvalidArgumentException, CLogicException, "Invalid argument")
POCO_IMPLEMENT_EXCEPTION(CNotImplementedException, CLogicException, "Not implemented")
POCO_IMPLEMENT_EXCEPTION(CRangeException, CLogicException, "Out of range")
POCO_IMPLEMENT_EXCEPTION(CIllegalStateException, CLogicException, "Illegal state")
POCO_IMPLEMENT_EXCEPTION(CInvalidAccessException, CLogicException, "Invalid access")
POCO_IMPLEMENT_EXCEPTION(CSignalException, CLogicException, "Signal received")
POCO_IMPLEMENT_EXCEPTION(CUnhandledException, CLogicException, "Signal received")

POCO_IMPLEMENT_EXCEPTION(CRuntimeException, CException, "Runtime exception")
POCO_IMPLEMENT_EXCEPTION(CNotFoundException, CRuntimeException, "Not found")
POCO_IMPLEMENT_EXCEPTION(CExistsException, CRuntimeException, "Exists")
POCO_IMPLEMENT_EXCEPTION(CTimeoutException, CRuntimeException, "Timeout")
POCO_IMPLEMENT_EXCEPTION(CSystemException, CRuntimeException, "System exception")
POCO_IMPLEMENT_EXCEPTION(CRegularExpressionException, CRuntimeException, "Error in regular expression")
POCO_IMPLEMENT_EXCEPTION(CLibraryLoadException, CRuntimeException, "Cannot load library")
POCO_IMPLEMENT_EXCEPTION(CLibraryAlreadyLoadedException, CRuntimeException, "Library already loaded")
POCO_IMPLEMENT_EXCEPTION(CNoThreadAvailableException, CRuntimeException, "No thread available")
POCO_IMPLEMENT_EXCEPTION(CPropertyNotSupportedException, CRuntimeException, "Property not supported")
POCO_IMPLEMENT_EXCEPTION(CPoolOverflowException, CRuntimeException, "Pool overflow")
POCO_IMPLEMENT_EXCEPTION(CNoPermissionException, CRuntimeException, "No permission")
POCO_IMPLEMENT_EXCEPTION(COutOfMemoryException, CRuntimeException, "Out of memory")
POCO_IMPLEMENT_EXCEPTION(CDataException, CRuntimeException, "Data error")

POCO_IMPLEMENT_EXCEPTION(CDataFormatException, CDataException, "Bad data format")
POCO_IMPLEMENT_EXCEPTION(CSyntaxException, CDataException, "Syntax error")
POCO_IMPLEMENT_EXCEPTION(CCircularReferenceException, CDataException, "Circular reference")
POCO_IMPLEMENT_EXCEPTION(CPathSyntaxException, CSyntaxException, "Bad path syntax")
POCO_IMPLEMENT_EXCEPTION(CIOException, CRuntimeException, "I/O error")
POCO_IMPLEMENT_EXCEPTION(CFileException, CIOException, "File access error")
POCO_IMPLEMENT_EXCEPTION(CFileExistsException, CFileException, "File exists")
POCO_IMPLEMENT_EXCEPTION(CFileNotFoundException, CFileException, "File not found")
POCO_IMPLEMENT_EXCEPTION(CPathNotFoundException, CFileException, "Path not found")
POCO_IMPLEMENT_EXCEPTION(CFileReadOnlyException, CFileException, "File is read-only")
POCO_IMPLEMENT_EXCEPTION(CFileAccessDeniedException, CFileException, "Access to file denied")
POCO_IMPLEMENT_EXCEPTION(CCreateFileException, CFileException, "Cannot create file")
POCO_IMPLEMENT_EXCEPTION(COpenFileException, CFileException, "Cannot open file")
POCO_IMPLEMENT_EXCEPTION(CWriteFileException, CFileException, "Cannot write file")
POCO_IMPLEMENT_EXCEPTION(CReadFileException, CFileException, "Cannot read file")
POCO_IMPLEMENT_EXCEPTION(CUnknownURISchemeException, CRuntimeException, "Unknown URI scheme")


POCO_IMPLEMENT_EXCEPTION(CApplicationException, CException, "Application exception")
POCO_IMPLEMENT_EXCEPTION(CBadCastException, CRuntimeException, "Bad cast exception")

POCO_IMPLEMENT_EXCEPTION(CConfigurationException, CException, "Configuration error");
POCO_IMPLEMENT_EXCEPTION(CThreadException, CException, "Threading error");
POCO_IMPLEMENT_EXCEPTION(CWin32Exception, CException, "Win32 error");
POCO_IMPLEMENT_EXCEPTION(CSDLException, CException, "SDL error");
POCO_IMPLEMENT_EXCEPTION(CGracefulException, CException, "Graceful exit"); /* User request to exit */
POCO_IMPLEMENT_EXCEPTION(CAbortException, CException, "Abort requested");  /* User request to abort */