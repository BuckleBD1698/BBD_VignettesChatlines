modded class ChatLine
{
	override void Set(ChatMessageEventParams params)
	{
		super.Set(params);

		if (params.param4 != "")
		{
			TextWidget nameWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemSenderWidget"));
			TextWidget textWidget = TextWidget.Cast(m_RootWidget.FindAnyWidget("ChatItemTextWidget"));

			if (nameWidget && textWidget)
			{
				int color = ColorNameToColor(params.param4);
				
				nameWidget.SetColor(color);
				textWidget.SetColor(color);
			}
		}
	}
}
