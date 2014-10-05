#ifndef FORWARD_FIRST_ORDER_LOGIC_H
#define FORWARD_FIRST_ORDER_LOGIC_H
#include <string>
#include <vector>
#include <boost/mpl/vector.hpp>
#include "sentence_helper.hpp"
namespace first_order_logic
{
	struct term;
	template< typename T >
	struct sentence;
	struct variable;
	struct atomic_sentence;
	term make_function( const std::string & s, const std::vector< term > & t );
	term make_constant( const std::string & s );
	term make_variable( const std::string & s );
	atomic_sentence make_predicate( const std::string & s, const std::vector< term > & t );
	atomic_sentence make_propositional_letter( const std::string & s );

	template< typename T >
	typename add_sentence_front< T, set_c< sentence_type, sentence_type::logical_not > >::type
	make_not( const T & s );

	template< typename T1, typename T2 >
	typename add_sentence_front
	<
		typename sentence_common< T1, T2 >::type,
		set_c< sentence_type, sentence_type::logical_and >
	>::type
	make_and( const T1 & l, const T2 & r );

	template< typename T1, typename T2 >
	typename add_sentence_front
	<
		typename sentence_common< T1, T2 >::type,
		set_c< sentence_type, sentence_type::logical_or >
	>::type
	make_or( const T1 & l, const T2 & r );

	template< typename T1, typename T2 >
	auto make_imply( const T1 & l, const T2 & r ) { return make_or( make_not( l ), make_not( r ) ); }

	template< typename T1, typename T2 >
	auto make_iff( const T1 & l, const T2 & r )
	{ return make_or( make_and( l, r ), make_and( make_not( l ), make_not( r ) ) ); }

	template< typename T >
	typename add_sentence_front< T, set_c< sentence_type, sentence_type::all > >::type
	make_all( const variable & l, const T & s );

	template< typename T >
	typename add_sentence_front< T, set_c< sentence_type, sentence_type::some > >::type
	make_some( const variable & l, const T & s );

	atomic_sentence make_equal( const term & l, const term & r );
}
#include "../first_order_logic.hpp"
#endif // FORWARD_FIRST_ORDER_LOGIC_H
