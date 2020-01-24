// Set new default font family and font color to mimic Bootstrap's default styling
Chart.defaults.global.defaultFontFamily = 'Nunito', '-apple-system,system-ui,BlinkMacSystemFont,"Segoe UI",Roboto,"Helvetica Neue",Arial,sans-serif';
Chart.defaults.global.defaultFontColor = '#858796';

function number_format(number, decimals, dec_point, thousands_sep) {
  // *     example: number_format(1234.56, 2, ',', ' ');
  // *     return: '1 234,56'
  number = (number + '').replace(',', '').replace(' ', '');
  var n = !isFinite(+number) ? 0 : +number,
    prec = !isFinite(+decimals) ? 0 : Math.abs(decimals),
    sep = (typeof thousands_sep === 'undefined') ? ',' : thousands_sep,
    dec = (typeof dec_point === 'undefined') ? '.' : dec_point,
    s = '',
    toFixedFix = function (n, prec) {
      var k = Math.pow(10, prec);
      return '' + Math.round(n * k) / k;
    };
  // Fix for IE parseFloat(0.55).toFixed(0) = 0;
  s = (prec ? toFixedFix(n, prec) : '' + Math.round(n)).split('.');
  if (s[0].length > 3) {
    s[0] = s[0].replace(/\B(?=(?:\d{3})+(?!\d))/g, sep);
  }
  if ((s[1] || '').length < prec) {
    s[1] = s[1] || '';
    s[1] += new Array(prec - s[1].length + 1).join('0');
  }
  return s.join(dec);
}

// Area Chart Example
var ctx = document.getElementById("myAreaChart");
var myLineChart = new Chart(ctx, {
  type: 'line',
  data: {
    labels: ["", "20s ago", "16s ago", "12s ago", "8s ago", "4s ago", "Now"],
    datasets: [{
      label: "Humidity",
      lineTension: 0.3,
      backgroundColor: "rgba(78, 115, 223, 0.05)",
      borderColor: "rgba(78, 115, 223, 1)",
      pointRadius: 3,
      pointBackgroundColor: "rgba(78, 115, 223, 1)",
      pointBorderColor: "rgba(78, 115, 223, 1)",
      pointHoverRadius: 3,
      pointHoverBackgroundColor: "rgba(78, 115, 223, 1)",
      pointHoverBorderColor: "rgba(78, 115, 223, 1)",
      pointHitRadius: 10,
      pointBorderWidth: 2,
      data: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
    }],
  },
  options: {
    maintainAspectRatio: false,
    layout: {
      padding: {
        left: 10,
        right: 25,
        top: 25,
        bottom: 0
      }
    },
    scales: {
      xAxes: [{
        time: {
          unit: 'date'
        },
        gridLines: {
          display: false,
          drawBorder: false
        },
        ticks: {
          maxTicksLimit: 7
        }
      }],
      yAxes: [{
        ticks: {
          steps: 10,
          stepValue: 10,
          max: 100,
          min: 0
        }
      }]
    },
    legend: {
      display: false
    },
    tooltips: {
      backgroundColor: "rgb(255,255,255)",
      bodyFontColor: "#858796",
      titleMarginBottom: 10,
      titleFontColor: '#6e707e',
      titleFontSize: 14,
      borderColor: '#dddfeb',
      borderWidth: 1,
      xPadding: 15,
      yPadding: 15,
      displayColors: false,
      intersect: false,
      mode: 'index',
      caretPadding: 10,
      callbacks: {
        label: function (tooltipItem, chart) {
          var datasetLabel = chart.datasets[tooltipItem.datasetIndex].label || '';
          return datasetLabel + ' : ' + number_format(tooltipItem.yLabel);
        }
      }
    }
  }
});

function updatechart(val) {
  myLineChart.data.datasets[0].data[0] = myLineChart.data.datasets[0].data[1];
  myLineChart.data.datasets[0].data[1] = myLineChart.data.datasets[0].data[2];
  myLineChart.data.datasets[0].data[2] = myLineChart.data.datasets[0].data[3];
  myLineChart.data.datasets[0].data[3] = myLineChart.data.datasets[0].data[4];
  myLineChart.data.datasets[0].data[4] = myLineChart.data.datasets[0].data[5];
  myLineChart.data.datasets[0].data[5] = myLineChart.data.datasets[0].data[6];
  myLineChart.data.datasets[0].data[6] = val;
  myLineChart.update();
}

function resetchart() {
  myLineChart.data.datasets[0].data[0] = 0.0;
  myLineChart.data.datasets[0].data[1] = 0.0;
  myLineChart.data.datasets[0].data[2] = 0.0;
  myLineChart.data.datasets[0].data[3] = 0.0;
  myLineChart.data.datasets[0].data[4] = 0.0;
  myLineChart.data.datasets[0].data[5] = 0.0;
  myLineChart.data.datasets[0].data[6] = 0.0;
  myLineChart.update();
}
