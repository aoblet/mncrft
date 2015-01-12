/**********************************************************************
Copyright (c) 2013 by Matt Swain <m.swain@me.com>

The MIT License

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

***********************************************************************/

// Copyright 2007-2010 Baptiste Lepilleur
// Distributed under MIT license, or public domain if desired and
// recognized in your jurisdiction.
// See file LICENSE for detail or copy at http://jsoncpp.sourceforge.net/LICENSE

#ifndef JSON_CWRITER_H_INCLUDED
#define JSON_CWRITER_H_INCLUDED
#include "value.h"
#include "writer.h"
#endif // if !defined(JSON_IS_AMALGAMATION)
#include <vector>
#include <string>

// Disable warning C4251: <data member>: <type> needs to have dll-interface to
// be used by...
#if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)
#pragma warning(push)
#pragma warning(disable : 4251)
#endif // if defined(JSONCPP_DISABLE_DLL_INTERFACE_WARNING)

namespace Json {

   /** \brief Writes a Value in <a HREF="http://www.json.org">JSON</a> format with custom formatting.
    *
    * The JSON document is written according to the rules specified in the constructor. Objects and
    * arrays are printed on a single line if they are below a certain length, otherwise they are 
    * indented. It is possible to output invalid json if the customizable parameters are specified
    * incorrectly. Set maxWidth to 0 to print output on a single line. 
    *
    * \sa Reader, Value
    */
   class JSON_API CustomWriter : public Writer
   {
   public:
      CustomWriter( std::string opencurly = "{",
                    std::string closecurly = "}",
                    std::string opensquare = "[",
                    std::string closesquare = "]",
                    std::string colon = ":",
                    std::string comma = ",",
                    std::string indent = "  ",
                    int maxWidth = 74);
      virtual ~CustomWriter(){}

   public: // overridden from Writer
      virtual std::string write( const Value &root );

   private:
      void writeValue( const Value &value, std::string &doc, bool forceSingleLine );
      bool isMultiline( const Value &value );
      void indent();
      void unindent();

      std::string document_;
      std::string indentString_;
      std::string opencurly_;
      std::string closecurly_;
      std::string opensquare_;
      std::string closesquare_;
      std::string colon_;
      std::string comma_;
      std::string indent_;
      int maxWidth_;
   };
   
}
