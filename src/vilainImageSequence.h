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
#ifndef VILAINIMAGESEQUENCE_H
#define VILAINIMAGESEQUENCE_H

#include <vilainObject.h>

namespace vilain
{
class vilainImageSequence : public vilainObject
{
public:
    /** Default constructor */
    vilainImageSequence();
    /** Default destructor */
    virtual ~vilainImageSequence();
    /** Copy constructor
     *  \param other Object to copy from
     */
    vilainImageSequence(const vilainImageSequence& other);
    /** Assignment operator
     *  \param other Object to assign from
     *  \return A reference to this
     */
    vilainImageSequence& operator=(const vilainImageSequence& other);
    /** Access _sequence
     * \return The current value of _sequence
     */
    ofxImageSequence getSequence()
    {
        return _sequence;
    }
    /** Set _sequence
     * \param val New value to set
     */
    void setSequence(ofxImageSequence val)
    {
        _sequence = val;
    }
protected:
private:
    ofxImageSequence _sequence; //!< Member variable "_sequence"
};
}
#endif // VILAINIMAGESEQUENCE_H
