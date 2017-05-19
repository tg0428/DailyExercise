#pragma once

namespace tg
{
	class graphic
	{
	public:
		graphic();
		~graphic();

	public:
		virtual bool create_graphic();
		virtual bool depth_first_traverse();

	private:

	};
} // namsespace tg