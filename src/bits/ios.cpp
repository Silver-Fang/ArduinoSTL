/*	Copyright (C) 2004 Garrett A. Kajmowicz

	This file is part of the uClibc++ Library.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#ifdef ARDUINO_ARCH_AVR
#include "ios_base.h"
#include "../serstream"
#include "iostream"

namespace std
{
#ifdef __UCLIBCXX_SUPPORT_CDIR__
	_UCXXLOCAL int ios_base::Init::init_cnt = 0; // Needed to ensure the static value is created
// Create buffers first
#ifdef __UCLIBCXX_SUPPORT_COUT__
	_UCXXEXPORT serialbuf _cout_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
	_UCXXEXPORT serialbuf _cin_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
	_UCXXEXPORT filebuf _cerr_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_CLOG__
	_UCXXEXPORT filebuf _clog_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_WCOUT__
	_UCXXEXPORT wserialbuf _wcout_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCIN__
	_UCXXEXPORT wserialbuf _wcin_filebuf(Serial);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCERR__
	_UCXXEXPORT wfilebuf _wcerr_filebuf;
#endif
#ifdef __UCLIBCXX_SUPPORT_WCLOG__
	_UCXXEXPORT wfilebuf _wclog_filebuf;
#endif
// Then create streams
#ifdef __UCLIBCXX_SUPPORT_COUT__
	_UCXXEXPORT ostream cout(&_cout_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CIN__
	_UCXXEXPORT istream cin(&_cin_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CERR__
	_UCXXEXPORT ostream cerr(&_cerr_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_CLOG__
	_UCXXEXPORT ostream clog(&_clog_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCOUT__
	_UCXXEXPORT wostream wcout(&_wcout_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCIN__
	_UCXXEXPORT wistream wcin(&_wcin_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCERR__
	_UCXXEXPORT wostream wcerr(&_wcerr_filebuf);
#endif
#ifdef __UCLIBCXX_SUPPORT_WCLOG__
	_UCXXEXPORT wostream wclog(&_wclog_filebuf);
#endif
#endif
#ifdef __UCLIBCXX_EXPAND_IOS_CHAR__

	template _UCXXEXPORT void basic_ios<char, char_traits<char>>::clear(iostate state);
	template _UCXXEXPORT void basic_ios<char, char_traits<char>>::setstate(iostate state);

#endif

	_UCXXEXPORT ios_base::fmtflags ios_base::flags(fmtflags fmtfl)
	{
		fmtflags temp = mformat;
		mformat = fmtfl;
		return temp;
	}

	_UCXXEXPORT ios_base::fmtflags ios_base::setf(fmtflags fmtfl)
	{
		return flags(flags() | fmtfl);
	}

	_UCXXEXPORT ios_base::fmtflags ios_base::setf(fmtflags fmtfl, fmtflags mask)
	{
		return flags((flags() & ~mask) | (fmtfl & mask));
	}

	_UCXXEXPORT streamsize ios_base::precision(streamsize prec)
	{
		streamsize temp = mprecision;
		mprecision = prec;
		return temp;
	}

	_UCXXEXPORT streamsize ios_base::width(streamsize wide)
	{
		streamsize temp = mwidth;
		mwidth = wide;
		return temp;
	}

	_UCXXEXPORT locale ios_base::imbue(const locale &loc)
	{
		locale retval = mLocale;
		mLocale = loc;
		return retval;
	}
}
#endif