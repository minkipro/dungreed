#include "stdafx.h"

template <typename T, UINT Xsize, UINT Ysize, UINT ITEMSIZE>
Inventory<T, Xsize, Ysize, ITEMSIZE>::Inventory()
{
	for (UINT i = 0; i < Ysize; i++)
	{
		for (UINT j = 0; j < Xsize; j++)
		{
			itemList[j][i] = nullptr;
		}
	}

	isActive = false;
	render = TEXTUREMG->GetRenderInfo(info.GetWorldMatrix());
	render->SetRender(false);
}

template <typename T, UINT Xsize, UINT Ysize, UINT ITEMSIZE>
Inventory<T, Xsize, Ysize, ITEMSIZE>::~Inventory()
{

}

template <typename T, UINT Xsize, UINT Ysize, UINT ITEMSIZE>
void Inventory<T, Xsize, Ysize, ITEMSIZE>::Update(T** item)
{
	if (isActive)
	{
		if (*item == nullptr)
		{
			if (KEYMANAGER->KeyDown(VK_LBUTTON))
			{
				*item = GetItem();
			}
		}
		else
		{
			if (KEYMANAGER->KeyUp(VK_LBUTTON))
			{
				SetItem(item);
			}
		}
	}
}

template<typename T, UINT Xsize, UINT Ysize, UINT ITEMSIZE>
void Inventory<T, Xsize, Ysize, ITEMSIZE>::InventoryUpDown(bool trueAndFalse)
{
	isActive = trueAndFalse;
	render->SetRender(true);
}

template <typename T, UINT Xsize, UINT Ysize, UINT ITEMSIZE>
void Inventory<T, Xsize, Ysize, ITEMSIZE>::SetItem(T** item)
{
	RECT temp;
	temp.left = info.translationVec.x;
	temp.top = info.translationVec.y;

	temp.right = temp.left + (Xsize + ITEMRIB) * ITEMSIZE;
	temp.left = temp.top + (Ysize + ITEMRIB)*ITEMSIZE;

	if (PtInRect(&temp, MOUSE->GetPosition()))
	{
		for (UINT i = 0; i < Ysize; i++)
		{
			for (UINT j = 0; j < Xsize; j++)
			{
				temp.left = (j + ITEMRIB) * ITEMSIZE;
				temp.right = temp.left + ITEMSIZE;
				temp.top = (i + ITEMRIB) * ITEMSIZE;
				temp.bottom = temp.top + ITEMSIZE;

				if (PtInRect(&temp, MOUSE->GetPosition()))
				{
					if (itemList[j][i] == nullptr)
					{
						itemList[j][i] = *item;
						*item = nullptr;
						return;
					}
					else
					{
						for (int k = 0; k < Ysize; k++)
						{
							for (int h = 0; h < Xsize; h++)
							{
								if (itemList[h][k] == nullptr)
								{
									itemList[h][k] = *item;
									*item = nullptr;
									return;
								}
							}
						}
					}

					return;
				}
			}
		}
	}

	return;
}

template <typename T, UINT Xsize, UINT Ysize, UINT ITEMSIZE>
T * Inventory<T, Xsize, Ysize, ITEMSIZE>::GetItem()
{
	RECT temp;
	temp.left = info.translationVec.x;
	temp.top = info.translationVec.y;

	temp.right = temp.left + (Xsize + ITEMRIB) * ITEMSIZE;
	temp.left = temp.top + (Ysize + ITEMRIB)*ITEMSIZE;

	if (PtInRect(&temp, MOUSE->GetPosition()))
	{
		for (UINT i = 0; i < Ysize; i++)
		{
			for (UINT j = 0; j < Xsize; j++)
			{
				temp.left = j * ITEMSIZE;
				temp.right = temp.left + ITEMSIZE;
				temp.top = i * ITEMSIZE;
				temp.bottom = temp.top + ITEMSIZE;

				if (PtInRect(&temp, MOUSE->GetPosition()))
				{
					T* temp = itemList[j][i];
					itemList[j][i] = nullptr;
					return temp;
				}
			}
		}
	}

	return nullptr;
}