//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//=============================================================================//

#ifndef CSTRIKEBUYMENU_H
#define CSTRIKEBUYMENU_H
#ifdef _WIN32
#pragma once
#endif

#include <vgui_controls/WizardPanel.h>
#include "cstrikerotatingplayerpanel.h"

#include <buymenu.h>

//-----------------------------------------------------------------------------
// These are maintained in a list so the renderer can draw a 3D character
// model on top of them.
//-----------------------------------------------------------------------------

class CCSBuyMenuPlayerImagePanel: public CCSRotatingPlayerImagePanel
{
public:
	typedef CCSRotatingPlayerImagePanel BaseClass;

	CCSBuyMenuPlayerImagePanel( vgui::Panel *pParent, const char *pName );
	virtual ~CCSBuyMenuPlayerImagePanel();
	virtual void ApplySettings( KeyValues *inResourceData );

public:
	float m_flViewXPos;
	float m_flViewYPos;
	float m_flViewZPos;
	float m_flViewFOV;
};

extern CUtlVector<CCSBuyMenuPlayerImagePanel*> g_BuyMenuPlayerImagePanels;

class BuyPresetEditPanel;
class BuyPresetButton;

namespace vgui
{
	class Panel;
	class Button;
	class Label;
}

enum
{
	NUM_BUY_PRESET_BUTTONS = 4,
};

class CCSBuyMenuImagePanel: public vgui::Panel
{
	typedef vgui::Panel BaseClass;

public:
	CCSBuyMenuImagePanel( vgui::Panel *pParent, const char *pName );
	virtual ~CCSBuyMenuImagePanel();
	virtual void ApplySettings( KeyValues *inResourceData );


public:
	char m_szWeaponName[80];
	float m_flViewXPos;
	float m_flViewYPos;
	float m_flViewZPos;
	float m_flViewFOV;
};

extern CUtlVector<CCSBuyMenuImagePanel*> g_BuyMenuImagePanels;

//============================
// Base CS buy Menu
//============================
class CCSBaseBuyMenu : public CBuyMenu
{
private:
	typedef vgui::WizardPanel BaseClass;

public:
	CCSBaseBuyMenu(IViewPort *pViewPort, const char *subPanelName);

	virtual void ShowPanel( bool bShow );
	virtual void Paint( void );
	virtual void SetVisible( bool state );

	//void HandleBlackMarket( void );

private:
	void UpdateBuyPresets( bool showDefaultPanel = false );	///< Update the Buy Preset buttons and their info panels on the main buy menu
	vgui::Panel *m_pMainBackground;
	BuyPresetButton *m_pBuyPresetButtons[NUM_BUY_PRESET_BUTTONS];
	//BuyPresetEditPanel *m_pLoadout;
	vgui::Label *m_pMoney;
	int m_lastMoney;

	//vgui::EditablePanel *m_pBlackMarket;
	HFont m_hUnderlineFont;

	// Background panel -------------------------------------------------------

public:
	virtual void PaintBackground();
	virtual void PerformLayout();
	virtual void ApplySchemeSettings( vgui::IScheme *pScheme );

	bool m_backgroundLayoutFinished;

	// End background panel ---------------------------------------------------

protected:
	virtual Panel* CreateControlByName( const char* controlName );

};

//============================
// CT main buy Menu
//============================
class CCSBuyMenu_CT : public CCSBaseBuyMenu
{
private:
	typedef vgui::WizardPanel BaseClass;

public:
	CCSBuyMenu_CT(IViewPort *pViewPort);

	virtual const char *GetName( void ) { return PANEL_BUY_CT; }
};


//============================
// Terrorist main buy Menu
//============================
class CCSBuyMenu_TER : public CCSBaseBuyMenu
{
private:
	typedef vgui::WizardPanel BaseClass;

public:
	CCSBuyMenu_TER(IViewPort *pViewPort);
	
	virtual const char *GetName( void ) { return PANEL_BUY_TER; }
};

#endif // CSTRIKEBUYMENU_H
