/*
 * vilain::, a set of visual object for video mapping and light light show
 *     Copyright (C) 2014 Gregory DAVID <groolot@groolot.net>
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef VILAINVIDEO_H
#define VILAINVIDEO_H

#include <vilainObject.h>

namespace vilain
{
class vilainVideo : public vilainObject
{
	public:
		/** Default constructor */
		vilainVideo();
		/** Default destructor */
		virtual ~vilainVideo();
		/** Copy constructor
		 *  \param other Object to copy from
		 */
		vilainVideo(const vilainVideo& other);
		/** Assignment operator
		 *  \param other Object to assign from
		 *  \return A reference to this
		 */
		vilainVideo& operator=(const vilainVideo& other);
	protected:
	private:
		string filePath;
		ofVideoPlayer video;
};
}
#endif // VILAINVIDEO_H
