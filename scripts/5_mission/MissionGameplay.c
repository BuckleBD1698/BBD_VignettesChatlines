modded class MissionGameplay
{
	protected Widget m_ChatBackground;
	protected float m_ChatBackgroundTimerValue;

	override void OnInit()
	{
		super.OnInit();

		if (m_HudRootWidget)
		{
			Widget chatFrame = m_HudRootWidget.FindAnyWidget("ChatFrameWidget");
			if (chatFrame)
			{
				m_ChatBackground = GetGame().GetWorkspace().CreateWidget(ImageWidgetTypeID, 0, 0, 1, 1, WidgetFlags.VISIBLE | WidgetFlags.IGNOREPOINTER | WidgetFlags.BLEND, ARGB(255, 0, 0, 0), 0, chatFrame);
				
				if (m_ChatBackground)
				{
					m_ChatBackground.SetPos(0.0, 0.6); 
					m_ChatBackground.SetSize(0.5, 0.4); 
					
					m_ChatBackground.SetAlpha(0.6); 
					
					m_ChatBackground.SetSort(-1);
					m_ChatBackground.Show(false);
				}
			}
		}
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);
		
		Input input = GetGame().GetInput();
		if (input.LocalPress("UAChatlinesContrastToggle", false))
		{
			if (m_ChatBackground)
			{
				bool isVisible = m_ChatBackground.IsVisible();
				
				if (isVisible)
				{
					m_ChatBackground.Show(false);
				}
				else
				{
					m_ChatBackground.Show(true);
					m_ChatBackground.SetAlpha(0.6); 
					m_ChatBackgroundTimerValue = 12.0; 
				}
			}
		}
		
		if (m_ChatBackground && m_ChatBackground.IsVisible())
		{
			if (m_ChatBackgroundTimerValue > 0)
			{
				m_ChatBackgroundTimerValue -= timeslice;
				
				if (m_ChatBackgroundTimerValue <= 2.0)
				{
					float alpha = 0.6 * (m_ChatBackgroundTimerValue / 2.0);
					m_ChatBackground.SetAlpha(alpha);
				}
				
				if (m_ChatBackgroundTimerValue <= 0)
				{
					m_ChatBackground.Show(false);
				}
			}
		}
	}

	override void OnEvent(EventType eventTypeId, Param params)
	{
		if (eventTypeId == ChatMessageEventTypeID)
		{
			ChatMessageEventParams chatParams = ChatMessageEventParams.Cast(params);
			if (chatParams)
			{
				string message = chatParams.param3;
				
				if (IsChatCommand(message, "!ooc"))
				{
					string contentOOC = StripCommand(message, "!ooc");
					// Format: (OOC: text)
					chatParams.param3 = "(OOC: " + contentOOC + ")";
					chatParams.param1 = 0;
					chatParams.param4 = "colorStatusChannel"; // Blue
				}
				else if (IsChatCommand(message, "!emote"))
				{
					string contentEmote = StripCommand(message, "!emote");
					// Format: text <emote>
					chatParams.param3 = contentEmote + " <emote>";
					chatParams.param1 = 0;
					chatParams.param4 = "colorFriendly"; // Green
				}
				else if (IsChatCommand(message, "!em"))
				{
					string contentEm = StripCommand(message, "!em");
					chatParams.param3 = contentEm + " <emote>";
					chatParams.param1 = 0;
					chatParams.param4 = "colorFriendly"; // Green
				}
			}
		}

		super.OnEvent(eventTypeId, params);
	}

	bool IsChatCommand(string message, string command)
	{
		if (message.Length() <= command.Length()) return false;
		string prefix = message.Substring(0, command.Length());
		prefix.ToLower();
		if (prefix == command)
		{
			string separator = message.Substring(command.Length(), 1);
			if (separator == " ") return true;
		}
		return false;
	}

	string StripCommand(string message, string command)
	{
		int len = command.Length() + 1;
		if (message.Length() <= len) return "";
		return message.Substring(len, message.Length() - len);
	}
}
