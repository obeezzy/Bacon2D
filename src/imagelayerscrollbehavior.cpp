/**
 * The MIT License (MIT)
 *
 * Copyright (C) 2014 Bacon2D Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "imagelayerscrollbehavior.h"

#include "bacon2dimagelayer.h"

Q_LOGGING_CATEGORY(imageLayerScrollBehavior, "bacon2d.core.imagelayerscrollbehavior", QtWarningMsg);

ImageLayerScrollBehavior::ImageLayerScrollBehavior(QObject *parent)
    : ScrollBehaviorImpl(parent)
{
}

void ImageLayerScrollBehavior::update(const int &delta)
{
    Q_UNUSED(delta);

    Bacon2DImageLayer *target = nullptr;
	if (!(target = dynamic_cast<Bacon2DImageLayer*>(m_target)))
		return;

	target->setHorizontalOffset(target->horizontalOffset() + m_horizontalStep);
	target->setVerticalOffset(target->verticalOffset() + m_verticalStep);

	if (target->horizontalOffset() <= -target->imageWidth())
		target->setHorizontalOffset(0);
	else if (target->horizontalOffset() >= 0)
		target->setHorizontalOffset(-target->imageWidth());

	if (target->verticalOffset() <= -target->imageHeight())
		target->setVerticalOffset(0);
	else if (target->verticalOffset() >= 0)
		target->setVerticalOffset(-target->imageHeight());
}
