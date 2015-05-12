#ifndef _JIA_XKALMAN_
#define _JIA_XKALMAN_

namespace XE{
class XKalmanFilter
{
private:
	double m_processNioseQ;
	double m_measureNoiseR;
	double m_initialPrediction;

	double m_xLast;
	double m_pLast;
public:
	double getQ() const{return m_processNioseQ;}
	void setQ(double q){m_processNioseQ = q;}
	double getR() const{return m_measureNoiseR;}
	void setR(double r){m_measureNoiseR = r;}
	double getP() const{return m_initialPrediction;}
	void setP(double p){m_initialPrediction = p;}
	double filter(double data)
	{
		double x_mid = m_xLast;
		double p_mid = m_pLast + m_processNioseQ;
		double kg = p_mid / (p_mid + m_measureNoiseR);
		m_xLast = x_mid + kg * (data - x_mid);
		m_pLast = (1 - kg) * p_mid;

		return m_xLast;
	}
	void init(double Q,double R,double P)
	{
		m_processNioseQ = Q;
		m_measureNoiseR = R;
		m_initialPrediction = P;
	}
	XKalmanFilter()
		:m_processNioseQ(0.0000001)
		,m_measureNoiseR(10.0)
		,m_initialPrediction(2210.0)
		,m_xLast(0.0)
		,m_pLast(0.0)
	{}
};

}
#endif