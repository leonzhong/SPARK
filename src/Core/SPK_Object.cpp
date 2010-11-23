//////////////////////////////////////////////////////////////////////////////////
// SPARK particle engine														//
// Copyright (C) 2008-2010 - Julien Fryer - julienfryer@gmail.com				//
//																				//
// This software is provided 'as-is', without any express or implied			//
// warranty.  In no event will the authors be held liable for any damages		//
// arising from the use of this software.										//
//																				//
// Permission is granted to anyone to use this software for any purpose,		//
// including commercial applications, and to alter it and redistribute it		//
// freely, subject to the following restrictions:								//
//																				//
// 1. The origin of this software must not be misrepresented; you must not		//
//    claim that you wrote the original software. If you use this software		//
//    in a product, an acknowledgment in the product documentation would be		//
//    appreciated but is not required.											//
// 2. Altered source versions must be plainly marked as such, and must not be	//
//    misrepresented as being the original software.							//
// 3. This notice may not be removed or altered from any source distribution.	//
//////////////////////////////////////////////////////////////////////////////////

#include <SPARK_Core.h>

namespace SPK
{
	void SPKObject::updateTransform(const WeakRef<const SPKObject>& parent)
	{
		SPK_ASSERT(parent != this,"SPKObject::updateTransform(const SPKObject*) - A SPKObject cannot be its own parent");
		transform.update(parent,*this);
	}

	IO::Descriptor SPKObject::exportAttributes() const
	{
		IO::Descriptor descriptor = createDescriptor();
		//descriptor.setName(name); //TODO
		innerExport(descriptor);
		return descriptor;
	}

	IO::Descriptor SPKObject::createDescriptor() const
	{
		std::vector<IO::Attribute> attributes;
		fillAttributeList(attributes);
		return IO::Descriptor(attributes);
	}

	void SPKObject::innerImport(const IO::Descriptor& descriptor)
	{
		const IO::Attribute* attrib = NULL;
		if (attrib = descriptor.getAttributeWithValue("transform"))
		{
			std::vector<float> t = attrib->getValuesFloat();
			if (t.size() == 16)
				transform.set(&t[0]);
		}
	}
	
	void SPKObject::innerExport(IO::Descriptor& descriptor) const
	{
		descriptor.getAttribute("transform")->setValuesFloat(transform.getLocal(),Transform::TRANSFORM_LENGTH,transform.isLocalIdentity());
	}
}
