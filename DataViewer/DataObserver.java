package dataviewer3;


public abstract class DataObserver {
	protected DataPlot m_dataPlot;
	
	public DataObserver(DataPlot dataplot) {
		this.m_dataPlot = dataplot;
	}
	
	public abstract void updateObserver();
}
