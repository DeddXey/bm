#ifndef LTDC429_H
#define LTDC429_H

#include "ltdc.h"
#include "rcc.h"
#include "dma2d.h"
#include "tim.h"


template<typename I, typename IF>
class Ltdc429 {


public:

	INLINE static uint16_t colorToLcd(const uint32_t color)
	{
		uint16_t out = ((color & 0xf80000) >> 8) |
		               ((color & 0xfc00) >> 5) |
		               ((color & 0xf8) >> 3);
		return out;
	}

	static void init()
	{
		I::preInit();

		Ltdc::clockEnable(true);
		Dma2D::clockEnable(true);

		Rcc::setLtdcClkDiv(Rcc::PllSaiDivr::divr8);

		Ltdc::enable(false);
		Ltdc::setSynchronizationSize(I::hSync - 1, I::vSync - 1);
		Ltdc::setBackporch(I::hBp + I::hSync - 1, I::vSync + I::vBp - 1);
		Ltdc::setActiveSize(I::activeWidth, I::activeHeight);
		Ltdc::setTotalSize(I::totalWidth, I::totalHeight);
		Ltdc::setBgColor(I::red, I::green, I::blue);
		LtdcLayer<1>::enable(true);
		Ltdc::setShadowReloadCfg(true, true);

		LtdcLayer<1>::setWindowHorizontalPosition(I::hBp + I::hSync,
		                                          I::hBp + I::hSync +
		                                          I::pixelWidth - 1);

		LtdcLayer<1>::setWindowVerticalPosition(I::vBp + I::vSync,
		                                        I::vBp + I::vSync + I::pixelHeight - 1);

		LtdcLayer<1>::setPixelFormat(PixelFormat::rgb565);
		LtdcLayer<1>::setFramebufferAddress(I::frameBufferAddress1);
		LtdcLayer<1>::setFramebufferLength(I::bpp * I::pixelWidth + 3,
		                                   I::bpp * I::pixelWidth);
		LtdcLayer<1>::setFramebufferLineNumber(I::pixelHeight);


		LtdcLayer<1>::setColor(I::red, I::green, I::blue);


		if constexpr (IF::layer2Enable) {
			LtdcLayer<2>::enable(IF::layer2Enable);



			LtdcLayer<2>::setWindowHorizontalPosition(I::hBp + I::hSync,
			                                          I::hBp + I::hSync +  IF::layer2Width - 1);

			LtdcLayer<2>::setWindowVerticalPosition(I::vBp + I::vSync + IF::layer2Y,
			                                        I::vBp + I::vSync + IF::layer2Y + IF::layer2Height - 1);

			LtdcLayer<2>::setPixelFormat(PixelFormat::rgb565);
			LtdcLayer<2>::setFramebufferAddress(I::frameBufferAddress2);
			LtdcLayer<2>::setFramebufferLength(I::bpp *  IF::layer2Width + 3,
			                                   I::bpp *  IF::layer2Width);
			LtdcLayer<2>::setFramebufferLineNumber(IF::layer2Height);


			LtdcLayer<2>::setColor(I::red, I::green, I::blue, 0);

		}
		Ltdc::setShadowReloadCfg(true, true);
		Ltdc::enable(true);
	}



	inline static volatile uint16_t* buff()
	{
		return reinterpret_cast<uint16_t*>(I::frameBufferAddress1);
	}

	static void drawPoint(int16_t x, int16_t y, uint32_t color)
	{
		*(buff() + x  + y * I::pixelWidth) = colorToLcd(color);
	}

	static void fillFrame(uint16_t x,
	                      uint16_t y,
	                      uint16_t width,
	                      uint16_t height,
	                      uint32_t color)
	{
		for (uint16_t dy = y; dy < (y + height); ++dy) {
			for (uint16_t dx = x; dx < (x + width); ++dx)
				drawPoint(dx, dy, color);
		}
	}

	//---------------------------------------------------------------
	///
	/// \brief Заполнение фрейма с использованием аппаратного ускорения
	/// \param x1 левый угол фрейма
	/// \param y1 верхний угол фрейма
	/// \param x2 правый угол фрейма
	/// \param y2 нижний угол фрейма
	/// \param color цвет
	/// \return 0 если успешно
	///
	static int8_t fillFrame1(int16_t x1,
	                         int16_t y1,
	                         int16_t x2,
	                         int16_t y2,
	                         uint32_t color)
	{

		while (Dma2D::isTransferInProgress()) {::simpleDelay(1);}


		Dma2D::setMode(Dma2D::mRegisterToMem);
		Dma2D::setPfcColorMode(PixelFormat::rgb565);
		Dma2D::setOutputColor(colorToLcd(color));
		Dma2D::setOutputOffset(I::pixelWidth - static_cast<uint16_t>(x2 - x1));
		Dma2D::setLines(static_cast<uint16_t>(y2 - y1), static_cast<uint16_t>(x2 - x1));
		Dma2D::setOutputMemoryAddress(I::frameBufferAddress1 +
		                              static_cast<uint32_t>(I::bpp * (I::pixelWidth * y1 + x1)));


		Dma2D::start();

		while (Dma2D::isTransferInProgress()) {::simpleDelay(1);}
//        while (Dma2D::isTransferComplete()) {simpleDelay(1);}

		Dma2D::clearTransferComplete();

		return 0;
	}
	//---------------------------------------------------------------
	///
	/// \brief Заполнение фрейма с использованием аппаратного ускорения
	/// \param x1 левый угол фрейма
	/// \param y1 верхний угол фрейма
	/// \param x2 правый угол фрейма
	/// \param y2 нижний угол фрейма
	/// \param color цвет
	/// \return 0 если успешно
	///
	static int8_t fillFrame2(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint32_t color)
	{

		//        RCC->AHB1ENR |= RCC_AHB1ENR_DMA2DEN;
		//        // ResetDMA
		//        RCC->AHB1RSTR |= RCC_AHB1RSTR_DMA2DRST;
		//        RCC->AHB1RSTR &= ~RCC_AHB1RSTR_DMA2DRST;

		while (Dma2D::isTransferInProgress()) {::simpleDelay(1);}


		Dma2D::setMode(Dma2D::mRegisterToMem);
		Dma2D::setPfcColorMode(PixelFormat::rgb565);
		Dma2D::setOutputColor(colorToLcd(color));
		Dma2D::setOutputOffset(IF::layer2Width - static_cast<uint16_t>(x2 - x1));
		Dma2D::setLines(static_cast<uint16_t>(y2 - y1), static_cast<uint16_t>(x2 - x1));
		Dma2D::setOutputMemoryAddress(I::frameBufferAddress2 +
		                              static_cast<uint32_t>(I::bpp * (IF::layer2Width * y1 + x1)));


		Dma2D::start();

		while (Dma2D::isTransferInProgress()) {::simpleDelay(1);}
//        while (Dma2D::isTransferComplete()) {simpleDelay(1);}

		Dma2D::clearTransferComplete();

		return 0;
	}

	static void drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color)
	{
		int16_t dx = static_cast<int16_t>(x2) - static_cast<int16_t>(x1);
		int16_t dy = static_cast<int16_t>(y2) - static_cast<int16_t>(y1);
		int16_t dxabs = (dx > 0) ? dx : -dx;
		int16_t dyabs = (dy > 0) ? dy : -dy;
		int8_t sgndx = (dx > 0) ? 1  : -1;
		int8_t sgndy = (dy > 0) ? 1  : -1;
		int16_t x = dyabs >> 1;
		int16_t y = dxabs >> 1;
		int16_t drawx = static_cast<int16_t>(x1);
		int16_t drawy = static_cast<int16_t>(y1);

		drawPoint(x1, y1, color);

		if(dxabs >= dyabs) {
			for(int16_t n = 0; n < dxabs; ++n) {
				y += dyabs;
				if(y >= dxabs) {
					y -= dxabs;
					drawy += sgndy;
				}
				drawx += sgndx;
				drawPoint(static_cast<uint16_t>(drawx), static_cast<uint16_t>(drawy), color);
			}
		}
		else {
			for(int16_t n = 0; n < dyabs; ++n) {
				x += dxabs;
				if(x >= dyabs) {
					x -= dyabs;
					drawx += sgndx;
				}
				drawy += sgndy;
				drawPoint(static_cast<uint16_t>(drawx), static_cast<uint16_t>(drawy), color);
			}
		}
	}

	//-----------------------------------------------------------------------------------------
	///
	/// \brief Копирование прямоугольного блока фреймбуфера во фреймбуфер
	/// \param xSrc координата x источника
	/// \param ySrc координата y источника
	/// \param xDst координата x приемника
	/// \param yDst координата y приемника
	/// \param width ширина блока
	/// \param height высота блока
	/// \return true если успешно
	///
	static bool copyBlock (int16_t xSrc, int16_t ySrc,
	                       int16_t xDst, int16_t yDst,
	                       uint16_t width, uint16_t height)
	{

		while (Dma2D::isTransferInProgress()) {::simpleDelay(1);}
		Dma2D::setMode(Dma2D::mMemToMem);
		Dma2D::setPfcColorMode(PixelFormat::rgb565);
		Dma2D::setForegroundColorMode(PixelFormat::rgb565);

		Dma2D::setLines(height, width);

		Dma2D::setForegroundOffset(I::pixelWidth - width);
		Dma2D::setForegroundMemoryAddress(I::frameBufferAddress1 +
		                                  static_cast<uint32_t>(I::bpp * (I::pixelWidth * ySrc + xSrc)));
		Dma2D::setOutputOffset(I::pixelWidth - width);
		Dma2D::setOutputMemoryAddress(I::frameBufferAddress1 +
		                              static_cast<uint32_t>(I::bpp * (I::pixelWidth * yDst + xDst)));


		Dma2D::start();
		while (Dma2D::isTransferInProgress()) {::simpleDelay(1);}

		return true;

	}


	//-----------------------------------------------------------------------------------------
	///
	/// \brief прокрутка прямоугольной области экрана по двум координатам
	/// \param x1 координата x левого верхнего угла области
	/// \param y1 координата y левого верхнего угла области
	/// \param width ширина области
	/// \param height высота области
	/// \param hScroll величина прокрутки по горизонтали
	/// \param vScroll величина прокрутки по вертикали
	/// \return
	///
	static int8_t scrollArea(int16_t x1, int16_t y1,
	                         uint16_t width, uint16_t height,
	                         int16_t hScroll, int16_t vScroll)
	{

		// Scroll to the right
		if (hScroll > 0) {

			uint16_t widthToCopy = width - static_cast<uint16_t>(hScroll);

			uint16_t blockWidth = 0;

			while (widthToCopy > 0) {

				if (widthToCopy > hScroll)
					blockWidth = static_cast<uint16_t>(hScroll);
				else
					blockWidth = widthToCopy;

				copyBlock(widthToCopy - blockWidth + x1,
				          y1,
				          widthToCopy + x1,
				          y1,
				          blockWidth,
				          height);

				widthToCopy -= blockWidth;

			}
			fillFrame(x1, y1, x1 + hScroll, y1 + height, 0);
		}

		// Scroll to the left
		if (hScroll < 0) {

//			copyBlock(x1 - hScroll,
//			          y1,
//			          x1,
//			          y1,
//			          width + static_cast<uint16_t>(hScroll),
//			          height);

//			fillFrame(x1 + width + hScroll, y1, x1 + width, y1 + height, 0);
		}

		// Scroll down
		if (vScroll > 0) {

			uint16_t heightToCopy = height - static_cast<uint16_t>(vScroll);

			uint16_t blockHeight = 0;

			while (heightToCopy > 0) {

				if (heightToCopy > vScroll)
					blockHeight = static_cast<uint16_t>(vScroll);
				else
					blockHeight = heightToCopy;

				copyBlock(x1,
				          heightToCopy - blockHeight + y1,
				          x1,
				          heightToCopy + y1,
				          width,
				          blockHeight);

				heightToCopy -= blockHeight;

			}
			fillFrame(x1, y1, x1 + width, y1 + vScroll, 0);
		}

		// Scroll up
		if (vScroll < 0) {

			copyBlock(x1,
			          y1 - vScroll,
			          x1,
			          y1,
			          width,
			          static_cast<uint16_t>(height + vScroll));

			fillFrame(x1, y1 + height + vScroll, x1 + width, y1 + height, 0);
		}

		return 0;
	}


};



#endif // LTDC429_H
