<?php
include_once 'Game.php';

class GameGoldenMasterTest extends \PHPUnit\Framework\TestCase
{
    private $master = 'master.txt';
    private $sample = 100;
    private $generation;

    public function setUp()
    {
        if (!file_exists($this->master)) {
            $this->fp = fopen($this->master, 'a');
            $this->generation = true;
        } else {
            $this->fp = fopen($this->master, 'r');
            $this->generation = false;
        }
    }

    public function tearDown()
    {
        fclose($this->fp);
    }

    public function testSeveralThousandsIterationProduceTheSameResultsAsTheGoldStandard()
    {
        srand(0);
        for ($i = 0; $i < $this->sample; $i++) {
            $output = $this->runAndCaptureOutput();
            $this->assertEqualToMaster($output);
        }
    }

    private function assertEqualToMaster($output)
    {
        if ($this->generation) {
            $this->storeInMaster($output);
        } else {
            $this->assertEquals($this->loadMasterRun(), $output);
        }
    }

    private function storeInMaster($output)
    {
        fputcsv($this->fp, explode("\n", $output));
    }

    private function loadMasterRun()
    {
        $run = fgetcsv($this->fp);
        return implode("\n", $run);
    }

    private function runAndCaptureOutput()
    {
        ob_start();
        include 'sandbox/GameRunner.php';
        $output = ob_get_contents();
        ob_end_clean();
        return $output;
    }
}
