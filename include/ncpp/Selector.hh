#ifndef __NCPP_SELECTOR_HH
#define __NCPP_SELECTOR_HH

#include <notcurses/notcurses.h>

#include "NCAlign.hh"
#include "Plane.hh"
#include "Utilities.hh"

namespace ncpp
{
	class NCPP_API_EXPORT Selector : public Root
	{
	public:
		static ncselector_options default_options;

	public:
		explicit Selector (Plane *plane, int y, int x, const ncselector_options *opts = nullptr)
			: Selector (static_cast<const Plane*>(plane), y, x, opts)
		{}

		explicit Selector (Plane const* plane, int y, int x, const ncselector_options *opts = nullptr)
			: Root (Utilities::get_notcurses_cpp (plane))
		{
			if (plane == nullptr)
				throw invalid_argument ("'plane' must be a valid pointer");
			common_init (Utilities::to_ncplane (plane), y, x, opts);
		}

		explicit Selector (Plane &plane, int y, int x, const ncselector_options *opts = nullptr)
			: Selector (static_cast<Plane const&>(plane), y, x, opts)
		{}

		explicit Selector (Plane const& plane, int y, int x, const ncselector_options *opts = nullptr)
			: Root (Utilities::get_notcurses_cpp (plane))
		{
			common_init (Utilities::to_ncplane (plane), y, x, opts);
		}

		~Selector ()
		{
			if (!is_notcurses_stopped ())
				ncselector_destroy (selector, nullptr);
		}

		int additem (const ncselector_item *item) const NOEXCEPT_MAYBE
		{
			return error_guard<int> (ncselector_additem (selector, item), -1);
		}

		int delitem (const char *item) const NOEXCEPT_MAYBE
		{
			return error_guard<int> (ncselector_delitem (selector, item), -1);
		}

		const char* previtem () const noexcept
		{
			return ncselector_previtem (selector);
		}

		const char* nextitem () const noexcept
		{
			return ncselector_nextitem (selector);
		}

		const char* get_selected () const noexcept
		{
			return ncselector_selected (selector);
		}

		bool offer_input (const struct ncinput* ni) const noexcept
		{
			return ncselector_offer_input (selector, ni);
		}

		Plane* get_plane () const noexcept;

	private:
		void common_init (ncplane *plane, int y, int x, const ncselector_options *opts = nullptr)
		{
			if (plane == nullptr)
				throw invalid_argument ("'plane' must be a valid pointer");

			selector = ncselector_create (plane, y, x, opts == nullptr ? &default_options : opts);
			if (selector == nullptr)
				throw init_error ("Notcurses failed to create a new selector");
		}

	private:
		ncselector *selector;
	};
}
#endif
