/*
    This file is a part of libcds - Concurrent Data Structures library

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2017

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "test_list_nogc.h"
#include <cds/container/michael_list_nogc.h>

namespace {
    namespace cc = cds::container;
    typedef cds::gc::nogc gc_type;

    class MichaelList_NOGC : public cds_test::list_nogc
    {};

    TEST_F( MichaelList_NOGC, less_ordered )
    {
        typedef cc::MichaelList< gc_type, item,
            typename cc::michael_list::make_traits<
                cds::opt::less< lt<item> >
            >::type
        > list_type;

        list_type l;
        test( l );
        test_ordered_iterator( l );
    }

    TEST_F( MichaelList_NOGC, compare_ordered )
    {
        typedef cc::MichaelList< gc_type, item,
            typename cc::michael_list::make_traits<
                cds::opt::compare< cmp<item> >
            >::type
        > list_type;

        list_type l;
        test( l );
        test_ordered_iterator( l );
    }

    TEST_F( MichaelList_NOGC, mix_ordered )
    {
        typedef cc::MichaelList< gc_type, item,
            typename cc::michael_list::make_traits<
                cds::opt::compare< cmp<item> >
                ,cds::opt::less< lt<item> >
            >::type
        > list_type;

        list_type l;
        test( l );
        test_ordered_iterator( l );
    }

    TEST_F( MichaelList_NOGC, item_counting )
    {
        struct traits : public cc::michael_list::traits
        {
            typedef lt<item> less;
            typedef cds::atomicity::item_counter item_counter;
        };
        typedef cc::MichaelList<gc_type, item, traits > list_type;

        list_type l;
        test( l );
        test_ordered_iterator( l );
    }

    TEST_F( MichaelList_NOGC, backoff )
    {
        struct traits : public cc::michael_list::traits
        {
            typedef lt<item> less;
            typedef cds::atomicity::item_counter item_counter;
            typedef cds::backoff::empty back_off;
        };
        typedef cc::MichaelList<gc_type, item, traits > list_type;

        list_type l;
        test( l );
        test_ordered_iterator( l );
    }

    TEST_F( MichaelList_NOGC, seq_cst )
    {
        struct traits : public cc::michael_list::traits
        {
            typedef lt<item> less;
            typedef cds::atomicity::item_counter item_counter;
            typedef cds::opt::v::sequential_consistent memory_model;
        };
        typedef cc::MichaelList<gc_type, item, traits > list_type;

        list_type l;
        test( l );
        test_ordered_iterator( l );
    }

    TEST_F( MichaelList_NOGC, stat )
    {
        struct traits: public cc::michael_list::traits
        {
            typedef lt<item> less;
            typedef cds::atomicity::item_counter item_counter;
            typedef cds::container::michael_list::stat<> stat;
        };
        typedef cc::MichaelList<gc_type, item, traits > list_type;

        list_type l;
        test( l );
        test_ordered_iterator( l );
    }

    TEST_F( MichaelList_NOGC, wrapped_stat )
    {
        struct traits: public cc::michael_list::traits
        {
            typedef lt<item> less;
            typedef cds::atomicity::item_counter item_counter;
            typedef cds::container::michael_list::wrapped_stat<> stat;
        };
        typedef cc::MichaelList<gc_type, item, traits > list_type;

        cds::container::michael_list::stat<> st;
        list_type l{ st };
        test( l );
        test_ordered_iterator( l );
    }

} // namespace
